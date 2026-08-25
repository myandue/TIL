# 워커 스레드풀 + 작업큐: 채팅 서버 통합 (eventfd)

## 1. 왜 스레드풀인가
- 현재 채팅 서버는 epoll 이벤트 루프 **한 스레드**가 read/파싱/broadcast/write을 전부 한다.
- 지금은 중간에 처리하는 로직이 간단한 `printf`정도라 괜찮지만, 해당 로직이 무거워진다면 그 시간동안 I/O 스레드를 필요로하는 다른 모든 클라가 멈춘다.
- 그래서, I/O 스레드는 바이트를 읽고 쓰기만하고, 완성된 메시지가 생기면 그것을 **작업 큐**로 던지고 본인은 바로 다음 소켓(클라)으로 간다. 워커 스레드풀이 큐에서 작업을 이어받아 처리하는 것이다.

## 2. 핵심 규칙: 공유 상태 소유권
- 작업을 워커로 넘기는 순간, 아래 공유 상태가 전부 **데이터 레이스 후보**가 된다.
    - `clients` 맵: 순회(broadcast) 중 다른 스레드가 erase -> 크래시
    - 각 클라의 `send_buf`: 동시에 append/write -> 버퍼 깨짐
    - `epoll_ctl`: 여러 스레드가 같은 fd 관심사 변경 -> 미정의 동작
- 규칙: 소켓·`clients`·`send_buf`·`epoll_ctl`은 오직 I/O 스레드만 만진다. **워커는 순수 계산만**
- 공유 데이터를 보호하는 방법
    | 방법 | 언제 | 코드 예시 |
    |---|---|---|
    | mutex로 잠그기 | 여러 스레드가 만져야 할 때 | outbox, tasks_ |
    | 한 스레드만 만질 수 있도록 국한(confine) | 가능하면 이게 나음 | clients, send_buf, 소켓 |
    - confine 이란, 애초에 잠글 필요도 없게 한 스레드만 만질 수 있도록 하는 것이다(경쟁이 없음).
    - 예로, clients 맵은 한 개의 I/O 스레드만이 접근한다. 워커는 아예 X. -> 잠글 필요도 없다. 

## 3. ThreadPool 클래스
- 작업 큐에 **"할 일 함수 자체"**를 담는다. `std::function<void()>`
- 멤버: `vector<thread> workers_`, `queue<function> tasks_`, `mtx_`, `cv_`, `running_`
- **worker_loop**: 큐에서 task를 꺼낼 때만 락. 해당 task(job)은 락 밖에서 한다.
- **enqueue**: 락 잡고 큐에 task `push`. `notify_one`은 락 풀고.
- 멤버 함수를 스레드로 돌리기: `std::thread(&ThreadPool::worker_loop, this)`
    - 스레드 생성에는 '할 일 함수', '함수에 줄 인자들'을 보낸다.
    - 위 경우는 '할 일 함수'가 자유함수일 경우이다.
    - '할 일 함수'가 '멤버함수(소속 클래스 존재)'일 경우, 두번째 인자로 '해당 함수를 어느 객체에서 실행할지(this)'를 보낸다. 
    - 그 경우 세번째 인자부터 '함수에 줄 인자들'인데, worker_loop의 경우 필요로 하는 인자가 없어서 세번째인자부터는 보낼 것이 없다.
    - 즉, 함수 worker_loop은 this 객체에서 실행되며, worker_loop은 this 객체 내의 멤버 변수를 사용할 수 있다..
- `emplace_back`: vector 함수. `push_back`은 원소를 벡터 뒤에서 바로 넣는 한편, `emplace_back`은 생성과 동시에 추가를 한다.

## 4. 워커 -> I/O 결과 반환 문제 (eventfd가 필요해진 계기)
- 워커가 직접 broadcast를 할 수 없음(clients와 소켓은 I/O 스레드 소유). 워커의 결과를 I/O에 돌려줘야한다.
- 결과를 **outbox(공유 큐)**에 넣는다. 넣는다한들, I/O 스레드는 `epoll_wait`에서 자고 있어서 outbox를 보지않는다.
    - `epoll_wait`은 **등록된 fd**가 ready될 때만 깨어난다. (outbox는 fd가 아니니까 epoll의 감시대상이 아니다.)
    - 그래서, 초기 `listen_fd`를 생성하는 시기에 `event_fd`도 생성해주고 사용한다.

## 5. eventfd
- 커널이 들고 있는 **64비트 카운터 하나**를 가진 fd.
- `eventfd(초기값, 플래그)`
    - `int event_fd = eventfd(0, EFD_NONBLOCK);`
    - 첫 인자는 카운터 초기값(0으로 시작)
    - 플래그는 읽을 것이 없다면 잠드는 것이 아니라 EAGAIN을 즉시 반환하라는 플래그.
- 큐에 task를 담아넣은 후, 그를 알리기 위해 eventfd에 8바이트를 write한다. 
    - eventfd의 변화로 인해 `epoll_wait`은 깨어나고, 거기서 eventfd를 읽고 0으로 리셋한다. 
    - eventfd의 숫자가 무엇인지는 중요치 않다. 그저 '알림'의 역할을 할 뿐이다.
    - eventfd로 깨어난 I/O 스레드는 공유 큐인 outbox를 체크해, 값이 존재할 경우 broadcast를 진행한다.

## 6. 전체 데이터 흐름
```
1. 소켓 EPOLLIN (클라가 보냄) - I/O 스레드 - read -> recv_buf 파싱 -> 완성된 줄(msg) 추출
        | Job(nickname, msg, fd) 만들어서 pool.enqueue
        ▼
2. 워커 스레드 - "무엇을 보낼지" 계산(처리) - OutMsg 생성 -> outbox에 push -> eventfd를 write(알림용)
        |
        ▼
3. event_fd EPOLLIN - I/O 스레드 깨어남 - eventfd를 read로 리셋 -> outbox큐를 local큐와 스왑(주소 교체) -> broadcast(실제 소켓 write)
        |
        ▼
4. 소켓 EPOLLOUT - I/O 스레드 - flush_send(send_buf에 남은 것 마저 전송)
```
- **I/O 스레드** = 1, 3, 4(실제 소켓 read/write)
- **워커 스레드** = 2(계산/처리만)
- 참고: 3에서 outbox큐를 local큐와 스왑해준 이유는, outbox큐 그대로 사용하며 broadcast를 진행할 때, outbox큐를 계속 점유하게되기 때문이다. outbox를 놓아주기 위해(워커 스레드가 사용할 수 있게 하기 위해) local큐라는 빈 큐를 생성해서 주소를 교환해주는 것이다.
### auto
- 타입 자동 추론
- 동적 변수는 아님. 컴파일 시점에 고정.
- ex.
    ```
    // auto 쓸 때
    auto end = std::chrono::steady_clock::now();

    // auto 안 쓸 때
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    ```

### endl
- 줄바꿈 + flush <- 즉시 출력
- "\n" <- 줄바꿈만. flush 안 함. 
- endl은 매번 버퍼를 비우는 것이기 때문에 약간 느리다. 때문에 실무에서는 평소엔 `\n`을 쓰고, 정말 즉시 출력해야할 때만 `flush` 하는 게 정석이다.

### 블로킹 & 동기 실행
- 싱글 스레드는 한 줄이 끝나야 다음 줄을 실행한다. (동기)
- 한 작업이 끝나지 않으면 그 뒤로는 시작도 못한다.
- 이게 "블로킹".
- 해결: epoll / 멀티스레드 -> 추후 

### 스택 vs 큐 (자료구조)
- 스택: LIFO (Last In First Out, 같은쪽에서 in/out, 최근 것 먼저) - 콜스택, Undo
- 큐: FIFO (First In First Out, 뒤로 넣고 앞에서 뺌, 먼저 온 것 먼저) - 대기열, 패킷처리
- STL: std::stack, std::queue
- 본인이 헷갈린 부분
    - 메모리의 스택과 자료구조의 스택을 헷갈렸다.
    - 스택 메모리의 형태가 스택 자료구조처럼 LIFO이기 때문에 스택 메모리라고 붙여진거라고 한다.
    - 스택의 자료구조를 가진 객체가 스택 메모리에 놓일 수도, 힙 메모리에 놓일 수도 있는 것이다.

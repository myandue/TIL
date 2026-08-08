# STL 컨테이너 (vector / map / unordered_map)

## vector (동적 배열)
- 배열의 크기를 정하지 않아도 된다.
- 원소 추가: `push_back(value)`
- 배열 크기: `size()`
- 인덱스 접근: `v[i]`
- 순회: `for (const auto& x: v)`

## unordered_map (key-value, 해시)
- key로 값을 찾는 dict이다.
- 추가/조회: `m[key] = value` / `m[key]`
- 존재 여부 확인: `m.count(key)`
- 삭제: `m.erase(key)`
- 순회: `for (const auto& pair: m)` - `p.first`: key / `p.second`: value
- key는 한 번 지정되면 변경 할 수 없다.(const)
- 조회 시, 없는 key 값을 조회하게 되면 에러 반환이 아니라 해당 key를 생성하고 value 타입의 기본값을 넣은뒤, 해당 값을 반환해준다. (ex. 숫자 0 / bool false / 문자열 "")
    -> 이게 유령 삽입을 발생시키기 때문에 주의해야한다. 실제 값을 읽어오기 전에 존재 여부를 파악해야한다.(count, find)
- count, erase의 경우에는 없는 key 값을 넣으면 0을 반환한다. 
- at에 없는 key 값을 넣으면 exception을 발생시킨다.

## map vs unordered_map
| | unordered_map | map |
|---|---|---|
| 구조 | 해시 | 트리 |
| 순서 | 없음 | key 정렬 |
| 속도 | 평균 O(1) | O(log n) |
| 언제 | 빠른 조회 | 정렬 필요 |

- 정렬이 있는 map이라 할지라도, vector처럼 인덱스 접근을 할 수는 없다. 

## 선택 기준
- 순서로 관리 -> vector
- key로 빠른 조회 -> unordered_map
- key로 조회 + 정렬 -> map

## 추가 기록
- auto는 타입을 자동으로 지정해 주는 것이다.
- unordered_map을 구성하는 pair의 경우 `std::pair<k, v>` 인데, 언급했다시피 key는 불변이다. 해서, 정확히는 `std::pair<const k-type, v-type>`이 되는 것이다. 
- auto를 이용해 unordered_map을 참조하게 되면, `auto& pair`는 `std::pair<const k-type, v-type>&`와 같은 것이 된다. 

## vector 내부 구조
- vector는 실제로 `data`(포인터) + `size` + `capacity`, 이렇게 세 가지 요소로 구성되어 있다.
- vector는 스택 메모리에 보관된다. 하지만 그 안에 넣는 원소들은 힙 메모리에 보관된다.
- vector의 `data`가 포인터라고 했는데, 그 포인터가 원소들을 실제로 보관하고 있는 힙 메모리의 배열의 주소를 가리킨다.
- `v[i]` = data 를 따라가서 i번째 값을 반환해 주는 것.
- 여기서 size는 원소들로 채워진 개수를 의미하고, 실제 힙 배열의 크기는 capacity이다. 일반적으로 capacity는 size보다 크거나 같다. 즉, 실제로는 해당 배열이 해당 vector의 size보다 크다는 것이다.
- 해서, `push_back`을 통해 값을 주입하면 배열이 여유가 있는 경우 바로 주입하고, capacity를 초과하게 되면 새로 배열을 생성하고 기존의 배열을 복사한 뒤 새 배열의 주소값을 반환하여 `data` 값이 갱신된다. (분할상환 O(1)). (+ 앞서 언급했다시피 일반적으로 capacity > size 이기 때문에 재할당이 빈번하게 일어나는 것은 아니다.)
- `reserve(n)`: capacity를 미리 확보하는 것이다. capacity가 값 추가에 비해 부족하면 배열 재생성 & 카피 & 재할당의 비용이 빈번하게 발생하기 때문에 미리 capacity 를 확보해놓는 것이다.
- dangling 주의: 재할당 발생 시 원소의 기존 주소가 낡을 수 있다.
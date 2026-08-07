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
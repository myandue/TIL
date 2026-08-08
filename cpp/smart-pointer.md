# 스마트포인터 (unique_ptr)

## 스마트포인터?
- raw 포인터: `new`를 통해 객체를 생성하면 raw 포인터를 반환해준다. 
- raw 포인터는 delete를 직접 해주어야한다. (`new`를 통해 생성하면 힙 메모리에 저장되기 때문) -> 까먹으면 메모리 누수 및 에러의 위험
- 스마트포인터: 자동 delete (포인터에 RAII 적용)

## unique_ptr (독점 소유)
- 생성: `std::make_unique<T>()` (≈ `new T()` + 자동관리)
- 사용: `p->멤버`, `*p` (raw 포인터처럼 사용)
- 복사: 불가. 이동(move)만 됨. 소유자는 하나. 소유권을 이전시킬 수 있음.

## 소유권 & 수명
- delete 시점: 현재 해당 객체를 소유중인 unique_ptr가, 본인(포인터)이 소속된 스코프를 벗어날 때.
- return: 함수를 호출한 쪽에 소유권을 이동시키며 해당 객체의 수명은 최종 소유자에게 달려있다.

## new vs make_unique
- new: raw 포인터 (직접 delete 필요)
- make_unique: unique_ptr (자동 delete)
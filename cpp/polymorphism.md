# 다형성과 아이템 시스템 (스마트포인터·소유권)

콘솔 RPG 아이템/인벤토리 만들면서 정리.

## 1. 상속(is-a)과 컴포지션(has-a)
- 상속: "A는 B다" (Player는 Character다) -> 멤버/메서드를 물려받음.
- 컴포지션: "A는 B를 가진다" (Game은 Player와 Monster를 멤버로 품음)

## 2. 순수 가상 함수 & 추상 클래스
- `virtual void use(Player&) = 0;`에서 `= 0`은 "본문 없음. 자식이 반드시 구현."의 의미.
- 순수 가상이 하나라도 있으면 추상 클래스 -> 객체를 직접 만들 수 없음. (Item 실체화 불가)
- Character의 attack은 구현체가 무엇이건 같은 동작이기 때문에 Character에서 구현하고 자식에게 상속.
- Item의 use의 경우 자식의 종류에 따라 구체 동작이 다르기 때문에 순수 가상 메서드로 정의.

## 3. override
- 자식이 부모의 virtual을 재정의할 때 쓰임.
- 시그니처를 실수로 다르게 쓰면 부모 메서드가 재정의 되는 것이 아니라, 새 함수가 되면서 다형성이 조용히 깨짐. 이걸 override를 붙여줌으로써 컴파일 에러로 잡아준다.
- (참고) 시그니처: 함수를 식별하는 요소들의 조합. ex. `함수 이름 + 매개변수(타입/개수/순서) + const`

## 4. 가상 소멸자
- 자식 객체를 소멸시킬 때 부모 타입 포인터(unique_ptr<Item>)를 사용할 경우, virtual이 없으면 포인터 타입을 보고 부모 소멸자(~Item())만을 호출하게 된다. -> 자식 객체의 부모 영역만 정리되고 자식 영역은 미정리 -> 누수로 이어짐.

## 5. 스마트포인터 & 소유권
- '아이템'은 한 곳에서만 소유하고 복제되면 안 됨. -> 단독 소유 unique_ptr. 아이템을 갖고 있는 inventory는 vector<unique_ptr<Item>>
- 복사 불가이기 때문에, 옮길 땐 소유권 이전의 형태(std::move) -> addItem / takeDrop
- make_unique<Potion>(...): unique_ptr 생성의 표준 방법

## 6. move-only 타입 & initializer_list
- Monster에 unique_ptr 멤버(드랍 아이템)가 생기면 Monster는 복사 불가(move-only)가 됨.
- 게임 초기 선언 시 Monster 리스트를 생성하는데, vector의 중괄호 초기화는 내부적으로 initializer_list를 거친다. (생성 후 카피함) -> 때문에 move-only 객체를 vector에 생성시킬 때 중괄호 초기화의 방식을 사용하면 안된다.
- (참고) - vector 초기화
    ```
    std::vector<int> a{1, 2, 3}; // 중괄호 초기화
    std::vector<int> b(3, 0); // 소괄호 초기화
    int c = 5; // 등호(copy) 초기화
    
    // Monster가 move-only가 아니었을 때, 아래와 같이 중괄호 초기화를 했었음
    monsters{ Monster(...), Monster(...) }

    // Monster가 move-only가 됐을 때는, 기본 생성자를 통해 빈 vector를 생성하고, 본문에서 해당 vector에 push_back하는 형태로 변경
    monsters.push_back(Monster(...));
    ```

## 7. this / *this
- this: 현재 객체의 포인터(Player*)
- *this: 그 객체 자체
- 해당 함수를 선언할 때 매개변수로 무엇을 요청했냐에 따라 this 혹은 *this를 넘긴다.
- ex. `item->use(*this)`처럼 넘길 때, use가 매개변수로 무엇을 요청했냐에 따라 `this`(포인터) 또는 `*this`(객체)를 넘긴다. 참조(`Player&`)를 요청했으면 `*this`, 포인터(`Player*`)면 `this`.

---
관련: [[inheritance]], [[smart-pointer]]
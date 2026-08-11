# 상속과 클래스 설계 

| 콘솔 RPG(console-rpg)에서 Character / Player / Monster를 만들며 정리

## 1. public 상속 (is-a 관계)
```
class Player : public Character { ... };
```
- "Player는 Charater다". Character의 멤버 (name/hp/attackPower)와 메서드(attack/takeDamage 등)를 그대로 물려받음.
- public 상속이라 외부에서도 Player/Monster를 Character로 취급 가능 -> `void attack(Character& target)` 하나로 Player/Monster 둘 다 받을 수 있음.
- private/protected 상속도 받을 수는 있음.

## 2. 자식 생성자 -> 부모 생성자 위임
```
Player::Player(std::string name, int hp, int attackPower)
    : Character(name, hp, attackPower), level(1)
{}
```
- 여기서 `Player::`는 "Player 클래스 소속"이라는 표시다. Player 클래스의 Player(...)를 구현한 것.
- 자식 객체 안에는 부모 부분이 통째로 들어있어서, 자식을 만들 때 부모 부분부터 지어야함.
- Character에 3인자 생성자만 있으므로, 초기화 리스트에서 `Character(...)`를 반드시 명시 호출해주어야한다. 빼먹으면 컴파일 에러.
- 부모 생성자 -> 자식 멤버 초기화 순서.

## 3. 멤버 초기화 리스트
```
: name(name), hp(hp), attackPower(attackPower) // 초기화
```
- `{ }` 이 안에서 `name=name`하고 넣는게 아니라 해당 중괄호 전에 위와 같이 초기화를 해줘야한다. 

## 4. 접근 지정자 & 캡슐화
- private: 이 클래스에서만 / protected: 나 + 자식 / public: 모두 가 접근 가능
- 멤버는 기본적으로 **private**. 해당 멤버에 접근하려면 public 메서드를 통해 접근하게 한다.(getter를 통해 값을 읽을 수 있도록하며, 직접 수정할 수 있는 setter의 선언은 지양한다. 상태변경은 takeDamage와 같은 '행동' 형태의 메서드로만 할 수 있도록한다.)

## 5. const 멤버 함수 (뒤 const)
```
int getHp() const;
```
- "이 함수는 객체를 바꾸지 않는다"는 약속
- const 멤버 함수여야 `const Character&` 같은 const 참조로도 호출이 가능하다. 
- 선언/정의 양쪽 다 뒤에 const를 붙여야한다.

## 6. 선언(.h) / 정의(.cpp) 분리
- C++ 빌드: 파일별 컴파일(.cpp -> .o) -> 링크(.o 합쳐서 실행 파일)
- .h: 선언(약속), 여러 cpp가 include 해서 공유.
- .cpp: 정의(함수 몸통), 딱 한 곳에만.
- 함수 **정의**를 헤더에 하게되면, 여러곳에서 include 했을 때 중복 정의를 하게 될 수 있다. -> 링커 에러(ODR, 한 정의 원칙).
- `.cpp`에서 정의할 땐 `Character::attack`처럼 소속을 `::`로 밝힘.
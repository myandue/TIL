#include <iostream>
#include <string>
#include <vector>

class Character {
public:
    // 데이터 (멤버 변수)
    int hp; // 체력
    int attackPower; // 공격력

    // 행동 (메서드)
    Character(int hp, int atk): hp(hp), attackPower(atk) {} // 생성자 - 초기 체력/공격력 설정
    void takeDamage(int dmg) {hp -= dmg;} // 데미지를 받음 (내 hp가 줄어듦)
    bool isAlive() {return hp > 0;} // 아직 살아있나? (hp > 0)
};

class Player: public Character {
public:
    Player(int hp, int atk)
        : Character(hp, atk) {}

    void attack(Monster& target) {target.takeDamage(attackPower);} // 몬스터를 공격 (target의 hp를 깎음)
};

class Monster: public Character {
public:
    std::string name; // 이름
    
    Monster(std::string name, int hp, int atk)
        : Character(hp, atk), name(name) {}
    void attack(Player& target) {target.takeDamage(attackPower);}; // 플레이어를 공격 (target의 hp를 깎음)
};

class Game {
public:
    // 데이터 (멤버 변수)
    Player player; // 플레이어 한 명
    std::vector<Monster> monsters; // 몬스터 목록 (방 순서대로)

    // 행동 (메서드)
    Game(); // 게임 초기화 (플레이어, 몬스터 세팅)
    void run(); // 게임 전체 진행 (메인 루프)
    void fight(Monster& m); // 한 몬스터와의 전투 처리
};
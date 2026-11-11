
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <utility>

using namespace std;

// =====================================
// 공통 함수
// =====================================

template<typename T>
T MaxValue(T a, T b)
{
    return a > b ? a : b;
}

constexpr int CalculateDamage(int damage, int multiplier)
{
    return damage * multiplier;
}

// =====================================
// 9-12 실습: Monster 클래스
// =====================================

class Monster
{
private:
    string name;

public:
    explicit Monster(string name)
        : name(std::move(name))
    {
    }

    void ShowInfo() const
    {
        cout << name << endl;
    }
};

// =====================================
// 4-10 실습: Player 클래스
// =====================================

class Player
{
private:
    int hp = 100;

public:
    int GetHp() const
    {
        return hp;
    }

    void ShowHp() const
    {
        cout << hp << endl;
    }
};

// =====================================
// 9-12 실습 실행
// =====================================

void RunPractice912()
{
    cout << "=== 9-12 실습 ===\n";

    // 문제 1: 템플릿과 constexpr
    cout << MaxValue(10, 20) << endl;
    cout << MaxValue(3.5, 1.5) << endl;

    constexpr int damage = CalculateDamage(30, 2);
    static_assert(damage == 60);

    cout << damage << endl;

    // 문제 2: STL 알고리즘
    vector<int> monsterHp = {100, 0, 300, 50, 0, 200};

    monsterHp.erase(
        remove_if(
            monsterHp.begin(),
            monsterHp.end(),
            [](int hp)
            {
                return hp == 0;
            }
        ),
        monsterHp.end()
    );

    sort(
        monsterHp.begin(),
        monsterHp.end(),
        greater<int>()
    );

    for (int hp : monsterHp)
    {
        cout << hp << " ";
    }

    cout << endl;

    // 문제 3: unique_ptr
    vector<unique_ptr<Monster>> monsters;

    auto goblin = make_unique<Monster>("Goblin");
    auto dragon = make_unique<Monster>("Dragon");
    auto slime = make_unique<Monster>("Slime");

    monsters.push_back(std::move(goblin));
    monsters.push_back(std::move(dragon));
    monsters.push_back(std::move(slime));

    for (const auto& monster : monsters)
    {
        monster->ShowInfo();
    }
}

// =====================================
// 4-10 실습 실행
// =====================================

void RunPractice410()
{
    cout << "\n=== 4-10 실습 ===\n";

    const Player player;

    cout << player.GetHp() << endl;
    player.ShowHp();

    constexpr int damage = CalculateDamage(20, 3);

    static_assert(damage == 60);

    vector<int> hp = {100, 200, 300};

    for (auto& n : hp)
    {
        n += 50;
    }

    for (const auto& n : hp)
    {
        cout << n << " ";
    }

    cout << endl;
}

// =====================================
// main 함수는 하나만 사용
// =====================================

int main()
{
    RunPractice912();
    RunPractice410();

    return 0;
}

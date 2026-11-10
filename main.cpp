#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <utility>

using namespace std;

// =====================================
// 문제 1. 템플릿 함수
// =====================================

template<typename T>
T MaxValue(T a, T b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

constexpr int CalculateDamage(int damage, int critical)
{
    return damage * critical;
}

// =====================================
// 문제 3. Monster 클래스
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
// main 함수는 하나만!
// =====================================

int main()
{
    // =================================
    // 문제 1
    // =================================

    cout << "=== 문제 1 ===\n";

    cout << MaxValue(10, 20) << endl;
    cout << MaxValue(3.5, 1.5) << endl;

    constexpr int damage = CalculateDamage(30, 2);

    static_assert(damage == 60);

    cout << damage << endl;

    // =================================
    // 문제 2
    // =================================

    cout << "\n=== 문제 2 ===\n";

    vector<int> monsterHp =
    {
        100, 0, 300, 50, 0, 200
    };

    // HP가 0인 몬스터 제거
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

    // HP 내림차순 정렬
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

    // =================================
    // 문제 3
    // =================================

    cout << "\n=== 문제 3 ===\n";

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

    return 0;
}
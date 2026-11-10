#include <iostream>
#include <vector>

using namespace std;

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

constexpr int CalculateDamage(int attack, int multiplier)
{
	return attack * multiplier;
}

int main()
{
	const Player player;

	cout << player.GetHp() << endl;
	player.ShowHp();

	constexpr int damage = CalculateDamage(20, 3);

	static_assert(damage == 60);

	vector<int> hp = { 100, 200, 300 };

	for (auto& n : hp)
	{
		n += 50;
	}

	for (const auto& n : hp)
	{
		cout << n << " ";
	}
}
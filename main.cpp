#include <iostream>
using namespace std;
class Enemy
{
private:
	int hp : hp(new int(100));
	inline static int count = 0;

public:
	Enemy(int hp)
	{
		this->hp = hp;
	}

	static int GetCount()
	{
		count++;
	}
	~Enemy()
	{

	}
};

int main()
{
	Enemy e1(100);

	{
		Enemy e2(50);
		cout << Enemy::GetCount() << endl;
	}

	cout << Enemy::GetCount() << endl;
}
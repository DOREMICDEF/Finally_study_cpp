#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
	int hp = -10;
	try
	{
		if (hp < 0)
		{
			throw runtime_error("잘못된 HP");
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		Test();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

class Resource
{
public:
	Resource()
	{
		cout << "생성\n";
	}
	~Resource()
	{
		cout << "소멸\n";
	}
};

void Test()
{
	Resource resource;

	throw runtime_error("오류 발생");
}

class Inventory
{
private:
	vector<int> items;

public:
	void AddItem(int id)
	{
		vector<int> temp = items;

		temp.push_back(id);

		if (id < 0)
		{
			throw runtime_error("예외 발생");
		}

		swap(temp, items);
	}
};
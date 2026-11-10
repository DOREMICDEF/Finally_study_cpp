#include <iostream>
#include <vector>

using namespace std;

// 문제 1. vector와 반복자

int main()
{
    vector<int> hp = { 100, 0, 50, 0, 80 };

    for (auto it = hp.begin(); it != hp.end(); ++it)
    {
        if (*it == 0)
        {
            it = hp.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (int n : hp)
    {
        cout << n << " ";
    }
}

// 문제 2. 이동 대입 연산자

class Gold
{
private:
    int* amount;

public:
    Gold(int value)
        : amount(new int(value))
    {
    }

    Gold(const Gold&) = delete;
    Gold& operator=(const Gold&) = delete;

    Gold(Gold&& other) noexcept
        : amount(other.amount)
    {
        other.amount = nullptr;
    }

    Gold& operator=(Gold&& other) noexcept
    {
        if (this != &other)
        {
            delete amount;

            amount = other.amount;
            other.amount = nullptr;
        }

        return *this;
    }

    ~Gold()
    {
        delete amount;
    }
};

// 문제 3. 예외 안전성
class Inventory
{
private:
    vector<int> items;

public:
    void AddItem(int id)
    {
        if (id < 0) {
            vector<int> temp = items;
            temp.push_back(id);
            swap(temp, items);
        }
    }
};
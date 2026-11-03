
#include <iostream>
#include <vector>
#include <array>
#include <deque>
using namespace std;

int main()
{
    // 1. vector: 동적 배열
    vector<int> v = { 10, 20, 30 };

    v.push_back(40);        // 뒤에 40 추가
    v.pop_back();           // 마지막 원소 삭제
    v.erase(v.begin() + 1); // 두 번째 원소 삭제

    v.reserve(100);         // 용량 확보
    v.resize(5);            // 원소 개수를 5개로 변경

    // 2. array: 고정 배열
    array<int, 3> a = { 10, 20, 30 };

    a[0] = 100;

    // 3. deque: 양쪽 끝에서 추가/삭제
    deque<int> d;

    d.push_back(20);
    d.push_front(10);
    d.pop_front();

    // 4. 출력
    cout << "vector: ";
    for (int n : v)
        cout << n << " ";

    cout << "\narray: ";
    for (int n : a)
        cout << n << " ";

    cout << "\ndeque: ";
    for (int n : d)
        cout << n << " ";

    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// =========================================
// 문제 1. 이진 탐색 함수
// =========================================

// const: 배열을 변경하지 않음
// &: 배열을 복사하지 않고 참조
// int: 찾은 인덱스를 반환, 없으면 -1
int BinarySearch(const vector<int>& arr, int target)
{
    int left = 0;
    int right = static_cast<int>(arr.size());

    // [left, right) 구간 탐색
    while (left < right)
    {
        int mid = left + (right - left) / 2;

        // 목표값을 찾았을 경우
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            // 목표값이 오른쪽에 존재
            left = mid + 1;
        }
        else
        {
            // 목표값이 왼쪽에 존재
            right = mid;
        }
    }

    // 값을 찾지 못한 경우
    return -1;
}

// =========================================
// 문제 3. 게임 이벤트 구조체
// =========================================

struct GameEvent
{
    string name;
    int triggerFrame;
};

// =========================================
// main 함수
// =========================================

int main()
{
    // -------------------------------------
    // 문제 1. 이진 탐색
    // -------------------------------------

    cout << "===== 문제 1: 이진 탐색 =====\n";

    vector<int> numbers = {
        4, 7, 11, 19, 24, 31, 42
    };

    // 함수 호출 후 반환값 출력
    cout << "19의 인덱스: "
        << BinarySearch(numbers, 19) << endl;

    cout << "20의 인덱스: "
        << BinarySearch(numbers, 20) << endl;


    // -------------------------------------
    // 문제 2. 중복 레벨 검색
    // -------------------------------------

    cout << "\n===== 문제 2: 중복 레벨 검색 =====\n";

    vector<int> levels = {
        10, 20, 20, 20, 30, 40
    };

    // 20 이상이 처음 등장하는 위치
    auto lower = lower_bound(
        levels.begin(),
        levels.end(),
        20
    );

    // 20 초과가 처음 등장하는 위치
    auto upper = upper_bound(
        levels.begin(),
        levels.end(),
        20
    );

    // 반복자를 인덱스로 변환
    int lowerIndex =
        static_cast<int>(lower - levels.begin());

    int upperIndex =
        static_cast<int>(upper - levels.begin());

    // 결과 출력
    cout << "lower_bound: "
        << lowerIndex << endl;

    cout << "upper_bound: "
        << upperIndex << endl;

    // 중복된 20의 개수
    cout << "레벨 20 아이템 개수: "
        << upperIndex - lowerIndex << endl;


    // -------------------------------------
    // 문제 3. 게임 이벤트 탐색
    // -------------------------------------

    cout << "\n===== 문제 3: 게임 이벤트 검색 =====\n";

    vector<GameEvent> events = {
        {"Attack", 100},
        {"Heal", 120},
        {"BossSpawn", 150},
        {"Reload", 120},
        {"Shield", 125}
    };

    // 이진 탐색을 하기 전에 먼저 정렬
    // 같은 프레임은 기존 순서 유지
    stable_sort(
        events.begin(),
        events.end(),
        [](const GameEvent& a, const GameEvent& b)
        {
            return a.triggerFrame < b.triggerFrame;
        }
    );

    // 120 이상인 첫 번째 이벤트 검색
    auto first = lower_bound(
        events.begin(),
        events.end(),
        120,
        [](const GameEvent& e, int frame)
        {
            return e.triggerFrame < frame;
        }
    );

    // 125 초과인 첫 번째 이벤트 검색
    auto last = upper_bound(
        events.begin(),
        events.end(),
        125,
        [](int frame, const GameEvent& e)
        {
            return frame < e.triggerFrame;
        }
    );

    // 검색된 구간의 이벤트 출력
    for (auto it = first; it != last; ++it)
    {
        cout << it->triggerFrame
            << " " << it->name
            << endl;
    }

    return 0;
}

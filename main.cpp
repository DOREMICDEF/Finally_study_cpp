
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// ========================================
// 문제 1. 삽입 정렬
// ========================================

void InsertionSort(vector<int>& arr)
{
    // 첫 번째 원소는 정렬된 상태로 간주
    for (size_t i = 1; i < arr.size(); i++)
    {
        // 현재 삽입할 값
        int key = arr[i];
        size_t j = i;

        // key보다 큰 원소를 오른쪽으로 이동
        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            j--;
        }

        // 올바른 위치에 key 삽입
        arr[j] = key;
    }
}

// ========================================
// 문제 2. 병합 정렬
// ========================================

// [left, right) 구간 정렬
void MergeSortRange(
    vector<int>& arr,
    vector<int>& temp,
    size_t left,
    size_t right)
{
    // 원소가 1개 이하이면 종료
    if (right - left <= 1)
        return;

    // 배열을 절반으로 나누기
    size_t mid = left + (right - left) / 2;

    // 왼쪽 부분 재귀 정렬
    MergeSortRange(arr, temp, left, mid);

    // 오른쪽 부분 재귀 정렬
    MergeSortRange(arr, temp, mid, right);

    // 두 배열을 병합
    size_t i = left;
    size_t j = mid;
    size_t k = left;

    // 양쪽 원소를 비교
    while (i < mid && j < right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    // 왼쪽에 남은 원소 복사
    while (i < mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // 오른쪽에 남은 원소 복사
    while (j < right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // 병합된 값을 원본 배열에 반영
    for (size_t index = left; index < right; index++)
    {
        arr[index] = temp[index];
    }
}

// 실제 호출할 함수
void MergeSort(vector<int>& arr)
{
    // 임시 배열은 한 번만 생성
    vector<int> temp(arr.size());

    MergeSortRange(arr, temp, 0, arr.size());
}

// ========================================
// 문제 3. 몬스터 정렬
// ========================================

struct Enemy
{
    string name;
    int threat;
    int distance;
    int spawnOrder;
};

// ========================================
// 정수 배열 출력 함수
// ========================================

void PrintNumbers(const vector<int>& arr)
{
    for (int n : arr)
    {
        cout << n << " ";
    }

    cout << "\n";
}

// ========================================
// 몬스터 상위 순위 출력 함수
// ========================================

void PrintTopEnemies(
    const vector<Enemy>& enemies,
    size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        const Enemy& e = enemies[i];

        cout << i + 1 << " "
            << e.name
            << " (" << e.threat
            << ", " << e.distance << ")\n";
    }
}

// ========================================
// main 함수 (하나만 작성)
// ========================================

int main()
{
    // ------------------------------------
    // 문제 1. 삽입 정렬
    // ------------------------------------

    cout << "[문제 1] 삽입 정렬\n";

    vector<int> numbers1 = { 9, 4, 1, 7, 3 };

    InsertionSort(numbers1);

    PrintNumbers(numbers1);

    // ------------------------------------
    // 문제 2. 병합 정렬
    // ------------------------------------

    cout << "\n[문제 2] 병합 정렬\n";

    vector<int> numbers2 =
    { 8, 3, 5, 1, 6, 2, 3 };

    MergeSort(numbers2);

    PrintNumbers(numbers2);

    // ------------------------------------
    // 문제 3. 몬스터 정렬
    // ------------------------------------

    vector<Enemy> enemies = {
        {"Goblin", 30, 8, 0},
        {"Orc", 60, 10, 1},
        {"Mage", 60, 3, 2},
        {"Boss", 100, 20, 3},
        {"Archer", 60, 3, 4}
    };

    // 람다 비교 함수
    auto compare = [](const Enemy& a, const Enemy& b)
        {
            // 1순위: 위협도가 높은 순서
            if (a.threat != b.threat)
            {
                return a.threat > b.threat;
            }

            // 2순위: 거리가 가까운 순서
            if (a.distance != b.distance)
            {
                return a.distance < b.distance;
            }

            // 3순위: 먼저 생성된 순서
            return a.spawnOrder < b.spawnOrder;
        };

    // 원본을 복사하여 전체 정렬
    vector<Enemy> sortedEnemies = enemies;

    sort(
        sortedEnemies.begin(),
        sortedEnemies.end(),
        compare
    );

    cout << "\n[문제 3] sort로 상위 3명\n";

    PrintTopEnemies(sortedEnemies, 3);

    // ------------------------------------
    // 심화. partial_sort 사용하기
    // ------------------------------------

    // 전체를 정렬하지 않고 상위 3개만 정렬
    partial_sort(
        enemies.begin(),
        enemies.begin() + 3,
        enemies.end(),
        compare
    );

    cout << "\n[심화] partial_sort로 상위 3명\n";

    PrintTopEnemies(enemies, 3);

    return 0;
}


#include <algorithm>   // min(), max()
#include <iostream>    // cout
#include <limits>      // numeric_limits
#include <stdexcept>   // invalid_argument
#include <string>      // string
#include <utility>     // pair
#include <vector>      // vector

using namespace std;

// 비용이나 피보나치 수를 저장할 자료형
using Cost = long long;

// ==========================================
// 1. Memoization (Top-down DP)
// ==========================================

// n: 구하려는 피보나치 수의 위치
//
// memo:
// 이미 계산한 결과를 저장하는 원본 배열
//
// 반환값:
// n번째 피보나치 수

Cost FibonacciMemo(
    int n,
    vector<Cost>& memo)
{
    // 재귀 종료 조건
    if (n <= 1)
    {
        return n;
    }

    // 이미 계산한 결과가 있다면
    // 재귀 계산을 반복하지 않는다.
    if (memo[n] != -1)
    {
        return memo[n];
    }

    // 작은 두 문제를 재귀적으로 해결
    Cost left = FibonacciMemo(n - 1, memo);
    Cost right = FibonacciMemo(n - 2, memo);

    // 결과를 저장해 다음 호출에서 재사용
    memo[n] = left + right;

    // 계산한 결과 반환
    return memo[n];
}

// ==========================================
// 2. Tabulation (Bottom-up DP)
// ==========================================

Cost FibonacciTab(int n)
{
    // 피보나치 결과를 저장할 배열
    vector<Cost> dp(n + 1, 0);

    // F(1) = 1 설정
    if (n >= 1)
    {
        dp[1] = 1;
    }

    // F(2)부터 F(n)까지 순서대로 계산
    for (int i = 2; i <= n; ++i)
    {
        // 이전 두 상태의 결과를 합산
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// ==========================================
// 3. Space Optimization
// ==========================================

Cost FibonacciOptimized(int n)
{
    // F(0), F(1) 처리
    if (n <= 1)
    {
        return n;
    }

    // 이전 두 상태만 저장
    Cost prev2 = 0;
    Cost prev1 = 1;

    for (int i = 2; i <= n; ++i)
    {
        // 현재 피보나치 수 계산
        const Cost current = prev1 + prev2;

        // 다음 계산에 필요한 값으로 이동
        prev2 = prev1;
        prev1 = current;
    }

    // 최종 계산값 반환
    return prev1;
}

// ==========================================
// 4. Coin Change — 최소 동전 개수
// ==========================================

// coins:
// 사용할 수 있는 양수 동전 종류
//
// amount:
// 만들고자 하는 목표 금액
//
// 반환값:
// 최소 동전 개수
// 만들 수 없는 경우 -1

int MinimumCoins(
    const vector<int>& coins,
    int amount)
{
    // 음수 금액은 허용하지 않는다.
    if (amount < 0)
    {
        throw invalid_argument(
            "Amount cannot be negative"
        );
    }

    // 동전 금액은 반드시 양수여야 한다.
    for (int coin : coins)
    {
        if (coin <= 0)
        {
            throw invalid_argument(
                "Coin values must be positive"
            );
        }
    }

    // 계산할 수 없는 상태를 나타내는 값
    const int INF = numeric_limits<int>::max();

    // dp[a]:
    // 금액 a를 만드는 데 필요한 최소 동전 수
    vector<int> dp(
        static_cast<size_t>(amount) + 1,
        INF
    );

    // 0원은 동전 0개로 만들 수 있다.
    dp[0] = 0;

    // 작은 금액부터 큰 금액까지 계산
    for (int a = 1; a <= amount; ++a)
    {
        // 각 동전을 마지막에 사용하는 경우 비교
        for (int coin : coins)
        {
            // 현재 금액보다 동전이 크면 불가능
            if (coin > a)
            {
                continue;
            }

            // 이전 금액을 만들 수 없는 경우 제외
            if (dp[a - coin] == INF)
            {
                continue;
            }

            // 이전 금액에 동전 1개 추가
            int candidate = dp[a - coin] + 1;

            // 현재 상태의 최소 동전 수 갱신
            dp[a] = min(dp[a], candidate);
        }
    }

    // 목표 금액을 만들 수 없다면 -1
    if (dp[amount] == INF)
    {
        return -1;
    }

    // 최소 동전 수 반환
    return dp[amount];
}

// ==========================================
// 5. 0/1 Knapsack — 최대 가치
// ==========================================

// items:
// pair<무게, 가치>로 구성된 아이템 목록
//
// capacity:
// 배낭의 최대 용량
//
// 반환값:
// 얻을 수 있는 최대 가치

Cost Knapsack01(
    const vector<pair<int, int>>& items,
    int capacity)
{
    if (capacity < 0)
    {
        throw invalid_argument(
            "Capacity cannot be negative"
        );
    }

    // dp[c]:
    // 현재까지 처리한 아이템만 사용하여
    // 용량 c 이하에서 얻는 최대 가치
    vector<Cost> dp(
        static_cast<size_t>(capacity) + 1,
        0
    );

    // 각 아이템을 하나씩 처리
    for (const auto& [weight, value] : items)
    {
        // 이 예제에서는 무게가 양수,
        // 가치는 음수가 아니라고 가정
        if (weight <= 0 || value < 0)
        {
            throw invalid_argument("Invalid item");
        }

        // 반드시 큰 용량부터 작은 용량으로 계산
        //
        // 이유:
        // 같은 아이템을 한 번만 사용할 수 있어야 함
        for (int c = capacity; c >= weight; --c)
        {
            // 현재 아이템을 선택하지 않는 경우
            Cost skip = dp[c];

            // 현재 아이템을 선택하는 경우
            Cost take = dp[c - weight] + value;

            // 더 높은 가치를 선택
            dp[c] = max(skip, take);
        }
    }

    // 최대 용량에서 얻는 최대 가치 반환
    return dp[capacity];
}

// ==========================================
// 6. Grid DP — 격자 최소 이동 비용
// ==========================================

// terrain:
// 0 이상의 값 = 해당 칸의 비용
// -1 = 통과할 수 없는 벽
//
// 이동 규칙:
// 오른쪽 또는 아래쪽으로만 이동 가능
//
// 시작점과 목표:
// (0,0) → (rows-1, cols-1)
//
// 시작점의 비용도 포함한다.
//
// 반환값:
// 최소 누적 이동 비용
// 도달 불가능한 경우 -1

Cost GridMinCost(
    const vector<vector<int>>& terrain)
{
    // --------------------------------------
    // STEP 1. 입력 검사
    // --------------------------------------

    if (terrain.empty() || terrain[0].empty())
    {
        throw invalid_argument(
            "Grid must not be empty"
        );
    }

    const size_t rows = terrain.size();
    const size_t cols = terrain[0].size();

    // 모든 행의 길이가 같은지 확인
    for (const auto& row : terrain)
    {
        if (row.size() != cols)
        {
            throw invalid_argument(
                "Grid must be rectangular"
            );
        }

        // -1만 벽으로 사용
        for (int cell : row)
        {
            if (cell < -1)
            {
                throw invalid_argument(
                    "Only -1 is a wall; costs must be nonnegative"
                );
            }
        }
    }

    // 시작점 또는 목표가 벽이라면 이동 불가능
    if (terrain[0][0] == -1 ||
        terrain[rows - 1][cols - 1] == -1)
    {
        return -1;
    }

    // --------------------------------------
    // STEP 2. DP 배열 생성
    // --------------------------------------

    const Cost INF =
        numeric_limits<Cost>::max() / 4;

    // 각 칸까지의 최소 누적 비용
    vector<vector<Cost>> dp(
        rows,
        vector<Cost>(cols, INF)
    );

    // 시작 칸 비용으로 초기화
    dp[0][0] = terrain[0][0];

    // --------------------------------------
    // STEP 3. Bottom-up 계산
    // --------------------------------------

    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            // 시작점은 이미 초기화했다.
            if (r == 0 && c == 0)
            {
                continue;
            }

            // 벽이라면 이동할 수 없다.
            if (terrain[r][c] == -1)
            {
                continue;
            }

            // 현재 칸에 도착하기 전까지의
            // 최소 누적 비용
            Cost best = INF;

            // 위쪽에서 현재 칸으로 내려오는 경우
            if (r > 0)
            {
                best = min(
                    best,
                    dp[r - 1][c]
                );
            }

            // 왼쪽에서 현재 칸으로 이동하는 경우
            if (c > 0)
            {
                best = min(
                    best,
                    dp[r][c - 1]
                );
            }

            // 이전 칸으로 이동할 수 있었다면
            // 현재 칸의 진입 비용을 추가
            //
            // 큰 값의 덧셈 범위를 확인한다.
            if (best != INF &&
                best <= INF - terrain[r][c])
            {
                dp[r][c] =
                    best + terrain[r][c];
            }
        }
    }

    // --------------------------------------
    // STEP 4. 결과 반환
    // --------------------------------------

    Cost answer = dp[rows - 1][cols - 1];

    // 목표가 도달 불가능한 상태라면 -1
    if (answer == INF)
    {
        return -1;
    }

    return answer;
}

// ==========================================
// 7. Longest Common Subsequence
// ==========================================

// a, b:
// 서로 비교할 두 문자열
//
// 반환값:
// 가장 긴 공통 부분 수열의 길이

int LCSLength(
    const string& a,
    const string& b)
{
    // dp[i][j]:
    // a의 앞 i개 문자와
    // b의 앞 j개 문자 사이의
    // LCS 길이
    //
    // 빈 문자열 상태가 필요하므로
    // 길이보다 한 칸 더 크게 생성
    vector<vector<int>> dp(
        a.size() + 1,
        vector<int>(b.size() + 1, 0)
    );

    // a의 접두사 길이
    for (size_t i = 1; i <= a.size(); ++i)
    {
        // b의 접두사 길이
        for (size_t j = 1; j <= b.size(); ++j)
        {
            // 현재 문자가 같은 경우
            if (a[i - 1] == b[j - 1])
            {
                // 이전 두 접두사의 공통 수열 + 1
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                // 현재 문자가 다르면
                // 한쪽 문자를 제외하는 두 경우 비교
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    // 두 문자열 전체의 LCS 길이 반환
    return dp[a.size()][b.size()];
}

// ==========================================
// 8. main 함수
// ==========================================

int main()
{
    // --------------------------------------
    // PART 1. 피보나치 DP 비교
    // --------------------------------------

    cout << "[1] Fibonacci\n";

    const int n = 10;

    // 메모이제이션 배열 생성
    vector<Cost> memo(n + 1, -1);

    cout << "Memo: "
        << FibonacciMemo(n, memo)
        << '\n';

    cout << "Tab: "
        << FibonacciTab(n)
        << '\n';

    cout << "Optimized: "
        << FibonacciOptimized(n)
        << "\n\n";

    // --------------------------------------
    // PART 2. Coin Change
    // --------------------------------------

    cout << "[2] Minimum coin change\n";

    // 1원, 3원, 4원 동전으로
    // 6원을 만드는 최소 동전 수
    //
    // 정답: 3 + 3 = 동전 2개
    cout << "Coins {1,3,4}, amount 6: "
        << MinimumCoins({ 1, 3, 4 }, 6)
        << "\n\n";

    // --------------------------------------
    // PART 3. 0/1 Knapsack
    // --------------------------------------

    cout << "[3] 0/1 Knapsack\n";

    // 아이템 {무게, 가치}
    //
    // A = {2, 3}
    // B = {3, 4}
    // C = {4, 5}
    //
    // 최대 용량 = 5
    //
    // A+B 선택 시 무게 5, 가치 7
    vector<pair<int, int>> items = {
        { 2, 3 },
        { 3, 4 },
        { 4, 5 }
    };

    cout << "Capacity 5, max value: "
        << Knapsack01(items, 5)
        << "\n\n";

    // --------------------------------------
    // PART 4. 격자 DP
    // --------------------------------------

    cout << "[4] Grid minimum cost\n";

    // 오른쪽 또는 아래쪽으로만 이동 가능
    //
    // -1은 벽
    //
    // 최단 경로:
    // (0,0) -> (0,1) -> (0,2)
    //                       |
    //                     (1,2)
    //                       |
    //                     (2,2)
    //
    // 누적 비용 = 1+3+1+1+1 = 7
    const vector<vector<int>> terrain = {
        { 1,  3, 1 },
        { 1, -1, 1 },
        { 4,  2, 1 }
    };

    cout << "Right/down path cost: "
        << GridMinCost(terrain)
        << "\n\n";

    // --------------------------------------
    // PART 5. LCS
    // --------------------------------------

    cout << "[5] Longest common subsequence\n";

    // GAMER와 GAME의
    // 최장 공통 부분 수열은 GAME
    //
    // 길이는 4
    cout << "LCS(GAMER, GAME): "
        << LCSLength("GAMER", "GAME")
        << '\n';

    return 0;
}

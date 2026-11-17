#include <vector>

using namespace std;

long long fibonacciMemo(
	int n,
	vector<long long>& memo)
{
	//memoization
	if (n <= 1)
	{
		return n;
	}

	if (memo[n] != -1)
	{
		return memo[n];
	}

	long long left = fibonacciMemo(n - 1, memo);
	long long right = fibonacciMemo(n - 2, memo);

	memo[n] = left + right;

	return memo[n];
}


int main()
{
	//coin
	vector<int> coins = { 1, 3, 4 };

	int amount = 6;

	const int INF = 100000000;

	vector<int> dp(amount + 1, INF);

	dp[0] = 0;
	
	for (int x = 1; x <= amount; x++)
	{
		for (int coin : coins)
		{
			if (coin > x)
			{
				continue;
			}

			if (dp[x - coin] == INF)
			{
				continue;
			}

			dp[x] = min(dp[x], dp[x - coin] + 1);
		}
	}
	// LCS
	for ( i = 1; i <= a.size(); i++)
	{
		for (size_t j = 1; j <= b.size(); j++)
		{
			if (a[i - 1] == b[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
}
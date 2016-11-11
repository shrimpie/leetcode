// Problem description:
// Say you have an array for which the ith element is the price of a given 
// stock on day i. 
// Design an algorithm to find the maximum profit. You may complete at most k 
// transactions.

// Note:
// You may not engage in multiple transactions at the same time (ie, you must 
// sell the stock before you buy again).



// Idea:
// dp[i][j]: the maximum profit you can get on jth day, completing i 
//           transactions.
// 1. dp[i][j] = max of
//    a) dp[i][j-1]: maximum profit before jth day.
//       That is, on jth day do nothing.
//    b) dp[i-1][m] + price[j] - price[m], m = 0..j-1.
//       That is, the best profit get on mth day, and plus the one buy on 
//       mth day, and sell on jth day, completing i transactions.
// 2. This formula can be simplified by observing the pattern:

// For example: 
// when j = 3 and i = 2
// m = 0: dp[1][0] - price[0] + price[3]
// m = 1: dp[1][1] - price[1] + price[3]
// m = 2: dp[1][2] - price[2] + price[3]

// when j = 4, i = 2
// m = 0: dp[1][0] - price[0] + price[4]
// m = 1: dp[1][1] - price[1] + price[4]
// m = 2: dp[1][2] - price[2] + price[4]
// m = 3: dp[1][3] - price[3] + price[4]

//        |     max_diff    |

// 1. The last item is constant for each day iteration.
// 2. The first jth differences (first two items) appear again at next 
//    iteration. So if we keep a max_diff to record current maximum difference,
//    then the m time iteration can be replaced by a constant operation.

// See the code below.




#include <iostream>
#include <vector>

using namespace std;



int solve_max_profit(vector<int>& prices)
{
	int res = 0;
	for(int i = 1; i < prices.size(); ++i)
		res += (prices[i] > prices[i-1]) ? prices[i] - prices[i-1] : 0;
	return res;
}

int max_profit(int k, vector<int>& prices)
{

	int n = prices.size();

	if(n == 0)
		return 0;

	if(k >= n)
		return solve_max_profit(prices);

	vector<vector<int> > dp(k+1, vector<int>(n, 0));
	for(int i = 1; i <= k; ++i)
	{
		int max_diff = -prices[0];
		for(int j = 1; j < n; ++j)
		{
			dp[i][j] = max(dp[i][j-1], prices[j] + max_diff);
			max_diff = max(max_diff, dp[i-1][j] - prices[j]);
		}
	}

	return dp[k][n-1];
}



int main()
{
	int k = 5;
	vector<int> prices { 1, 2, 3, 2, 3, 4, 5, 6, 7 };

	cout << "Test case returns "
	     << (max_profit(k, prices) == 7 ? "True" : "False")
	     << endl;




	return 0;
}


// Problem description:
// A robot is located at the top-left corner of a mxn grid (marked 'Start' in
// the diagram below).
// The robot can only move either down or right at any point in time. The robot
// is trying to reach the bottom-right corner of the grid (marked 'Finish' in
// the diagram below).
// How many possible unique paths are there?

// -----------------------------
// |Start|    |    |    |      |
// -----------------------------
// |     |    | .. |    |      |
// -----------------------------
// |     |    |    |    |Finish|
// -----------------------------

// Idea:
// dp[i][j]: the path numbers from the start to position (i,j).
// 1. Obviously, dp[i][j] = dp[i-1][j] + dp[i][j-1].
// 2. dp[0][j] = dp[i][0] = 1.
// 3. Direction from top to bottom, from left to right, can use 



#include <iostream>
#include <vector>

using namespace std;

int unique_paths(int m, int n)
{
	if(m < 1 || n < 1)
		return 0;
	vector<int> dp(n, 1);
	for(int i = 1; i < m; ++i)
	{
		for(int j = 1; j < n; ++j)
			dp[j] += dp[j-1];
	}

	return dp[n-1];
}


int main()
{
	vector<int> ms { 1, 3, 5, 7 };
	vector<int> ns { 2, 4, 6, 8 };
	vector<int> tgt { 1, 10, 126, 1716 };

	for(int i = 0; i < ms.size(); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
		     << (unique_paths(ms[i], ns[i]) == tgt[i] ? "True" : "False")
		     << endl;
	}


	return 0;
}


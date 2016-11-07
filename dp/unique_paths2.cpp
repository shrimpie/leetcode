// Problem description:
// Follow up for "Unique Paths":
// Now consider if some obstacles are added to the grids. How many unique paths
// would there be?

// An obstacle and empty space is marked as 1 and 0 respectively in the grid.
// 

// Idea:
// dp[i][j]: the path numbers from the start to position (i,j).
// There are some differences here:
// 1. dp[i][j] = 0 if (i,j) has an obstacle.
// 2. dp[0][j] = obstacleGrid[0][j] ? 0 : dp[0][j-1];
//    dp[i][0] = obstacleGrid[i][0] ? 0 : dp[i-1][0].
// 3. If obstacleGrid[0][0] = 1, return 0. 



#include <iostream>
#include <vector>

using namespace std;

int unique_paths(vector<vector<int> >& og)
{
	if(og.empty() || og[0].empty() || og[0][0] == 1)
		return 0;
	int m = og.size(), n = og[0].size();
	vector<int> dp(n, 1);
	for(int j = 1; j < n; ++j)
		dp[j] = og[0][j] ? 0 : dp[j-1];

	for(int i = 1; i < m; ++i)
	{
		dp[0] = og[i][0] ? 0 : dp[0];
		for(int j = 1; j < n; ++j)
			dp[j] = og[i][j] ? 0 : dp[j-1] + dp[j];
	}

	return dp[n-1];
}


int main()
{
	vector<vector<int> > og {{0,0,0}, {0,1,0}, {0,0,0}};
	cout << "Test case 1 returns "
	     << (unique_paths(og) == 2 ? "True" : "False")
	     << endl;

	vector<vector<int> > og2 {{0,0,0,1}, {0,1,0,0}, {0,0,0,0}, {0,0,0,0}};
	cout << "Test case 2 returns "
	     << (unique_paths(og2) == 7 ? "True" : "False")
	     << endl;


	return 0;
}


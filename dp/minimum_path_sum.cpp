// Problem description:
// Given a mxn grid filled with non-negative numbers, find a path from top left
// to bottom right which minimizes the sum of all numbers along its path.
// Note: You can only move either down or right at any point in time.

// Idea:
// dp[i][j]: minimum path sum ending at current position (i,j).
// 1. Formula: dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]).




#include <iostream>
#include <vector>

using namespace std;


int min_path_sum(vector<vector<int>>& grid) {
        
    if(grid.size() == 0)
        return 0;
    
    int rows = grid.size();
    int cols = grid[0].size();
    
    vector<vector<int>> d(rows, vector<int>(cols, 0));
    
    d[0][0] = grid[0][0];
    
    for(int i = 1; i < rows; ++i)
        d[i][0] = d[i-1][0] + grid[i][0];
    
    for(int j = 1; j < cols; ++j)
        d[0][j] = d[0][j-1] + grid[0][j];
    
    for(int i = 1; i < rows; ++i)
    {
        for(int j = 1; j < cols; ++j)
            d[i][j] = grid[i][j] + min(d[i-1][j], d[i][j-1]);
    }
    
    return d[rows-1][cols-1];
}



int main()
{
	vector<vector<int> > grid {{1,2,3,4}, {2,3,4,5}, {6,5,4,3}, {2,3,4,8}};
	cout << "Test case 1 return " 
	     << (min_path_sum(grid) == 25 ? "True" : "False")
	     << endl;


	return 0;
}


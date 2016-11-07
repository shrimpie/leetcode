// Problem description:

// Given a 2D matrix filled with 0's and 1's, find the largest rectangle 
// containing only 1's and return its area.

// For example, given the following matrix:

// 1 0 1 0 0
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0

// Return 6.

// Idea:
// 1. This one is closely related to the largest rectangle in histogram problem.
// 2. Each row of the matrix can be transformed to a histogram, so from each 
//    column you can do this histogram scan, and you can get the area.



#include <iostream>
#include <vector>

using namespace std;


int maximal_rectangle(vector<vector<char> >& matrix)
{
	if(matrix.size() == 0 || matrix[0].size() == 0)
		return 0;

	int m = matrix.size(), n = matrix[0].size();
	// Get the histogram.
	// The extra row and col memory is for boundaries occasions like the -1 
	// in the histogram problem.
	vector<vector<int> > mat(m + 1, vector<int>(n + 1, 0));
	for(int i = 0; i < m; ++i)
	{
		for(int j = n - 1; j >= 0; --j)
			mat[i][j] = matrix[i][j] == '1' ? (1 + mat[i][j+1]) : 0;
	}

	int ans = 0;
	// From each column, scan the histogram.
	for(int col = 0; col < n; ++col)
	{
		int row = 0;
		vector<int> s; // works as a stack here.
		while(row != mat.size())
		{
			if(s.empty() || mat[row][col] >= mat[s.back()][col])
				s.push_back(row++);
			else
			{
				int t = s.back();
				s.pop_back();
				int width = s.empty() ? row : row - s.back() - 1;
				ans = max(ans, mat[t][col] * width);
			}
		}
	}

	return ans;
}





int main()
{
	vector<vector<char> > matrix { {'1', '0', '1', '0', '0'},
	                               {'1', '0', '1', '1', '1'},
	                               {'1', '1', '1', '1', '1'},
	                               {'1', '0', '0', '1', '0'} };

	cout << "Test case 1 returns "
	     << (maximal_rectangle(matrix) == 6 ? "True" : "False")
	     << endl;

	return 0;
}


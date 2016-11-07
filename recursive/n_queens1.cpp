// The n-queens puzzle is the problem of placing n queens on an nxn chessboard 
// such that no two queens attack each other.
// Given an integer n, return all distinct solutions to the n-queens puzzle.

// I think this one should be n-queens 2 and the other one should 1, since it's
// harder. Well, not that harder, now you got the col_for_rows array, just add 
// queen to board, and store the results.
// 

#include <iostream>
#include <vector>

using namespace std;

void add_board(vector<vector<string> >& ans, vector<int>& col_for_rows)
{
	vector<string> sol;
	int size = col_for_rows.size();
	for(int i = 0; i < size; ++i)
	{
		string row = "";
		for(int j = 0; j < size; ++j)
		{
			if(j == col_for_rows[i])
				row.append("Q");
			else
				row.append(".");
		}
		sol.push_back(row);
	}
	ans.push_back(sol);
}

bool check(int row, vector<int>& col_for_rows)
{
	for(int i = 0; i < row; ++i)
	{
		int diff = abs(col_for_rows[i] - col_for_rows[row]);
		if(diff == 0 || diff == row - i)
			return false;
	}
	return true;
}

void place_queen(int row, vector<int>& col_for_rows, vector<vector<string> >& ans)
{
	if(row == col_for_rows.size())
	{
		add_board(ans, col_for_rows);
		return;
	}
	for(int i = 0; i < col_for_rows.size(); ++i)
	{
		col_for_rows[row] = i;
		if(check(row, col_for_rows))
			place_queen(row + 1, col_for_rows, ans);
	}
}

vector<vector<string> > solve_queens(int n)
{
	vector<vector<string> > ans;
	vector<int> col_for_rows(n);
	place_queen(0, col_for_rows, ans);

	return ans;
}


int main()
{
	int queens = 4;

	auto ans = solve_queens(queens);
	
	// This test case is portable, since the sequence of each solution is not 
	// determined. If you want it to be fixed, sort it first.
	cout << "Test case 1 returns "
	     << ((ans.size() == 2 && 
	     	  ans[0].size() == 4 &&
	     	  ans[0][0] == ".Q.." && ans[0][1] == "...Q" && 
	     	  ans[0][2] == "Q..." && ans[0][3] == "..Q." &&
	     	  ans[1].size() == 4 &&
	     	  ans[1][0] == "..Q." && ans[1][1] == "Q..." && 
	     	  ans[1][2] == "...Q" && ans[1][3] == ".Q..")
	      	  ? "True" : "False")
	     << endl;


	return 0;
}




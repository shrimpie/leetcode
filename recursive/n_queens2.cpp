// The n-queens puzzle is the problem of placing n queens on an nxn chessboard 
// such that no two queens attack each other.
// Given an integer n, return the total number of distinct solutions.


// The key here is to check if a configuration is invalid. Remember the rule: 
// a queen can attack another if they are in line horizontally, or vertically 
// or diagnally.
// You can use an array to record which column each queen is put for each row.
// If they are in the same column, or the absolute value of the difference of 
// their columns are equal to the row r to put, and previous columns (i) taken.
// Wow, this is really not interesting..
// Please check the code below, you'll see.


#include <iostream>
#include <vector>

using namespace std;


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

void place_queen(int row, vector<int>& col_for_rows, int& count)
{
	if(row == col_for_rows.size())
	{
		++count;
		return;
	}
	for(int i = 0; i < col_for_rows.size(); ++i)
	{
		col_for_rows[row] = i;
		if(check(row, col_for_rows))
			place_queen(row + 1, col_for_rows, count);
	}
}

int total_queens(int n)
{
	int count = 0;
	vector<int> col_for_rows(n);
	place_queen(0, col_for_rows, count);

	return count;
}


int main()
{
	// vector<int> queens { 1, 2, 3, 4, 5, 6, 7 };
	vector<int> tgt { 1, 0, 0, 2, 10, 4, 40, 92, 352, 724 };
	for(int i = 1; i <= 10; ++i)
	{
		cout << "Test case " << i << " returns "
		     << (total_queens(i) == tgt[i-1] ? "True" : "False")
		     << endl;
	}


	return 0;
}




// Given a matrix of mxn elements (m rows, n columns), return all elements of 
// the matrix in spiral order.
// For example,
// Given the following matrix:
// [
//    [1, 2, 3],
//    [4, 5, 6],
//    [7, 8, 9]
// ]
// You should return [1,2,3,6,9,8,7,4,5].


// Idea:
// Just keep an eye on how many levels you should loop, and each loop's start 
// and end index.

//


#include <iostream>
#include <vector>

using namespace std;

vector<int> spiral_order(vector<vector<int> >& matrix)
{
	vector<int> ret;
    if(matrix.empty() || matrix[0].empty())
        return ret;

    int m = matrix.size(), n = matrix[0].size();
    int nlvl = (min(m, n) + 1) / 2;
    for(int i = 0; i < nlvl; ++i)
    {
        int lastRow = m - 1 - i;
        int lastCol = n - 1 - i;
        if(lastRow == i)      // one row remain
        {
            for(int j = i; j <= lastCol; ++j)
                ret.push_back(matrix[i][j]);
        }
        else if(lastCol == i) // one col remain
        {
            for(int j = i; j <= lastRow; ++j)
                ret.push_back(matrix[j][i]);
        }   
        else
        {
            for(int j = i; j < lastCol; ++j) 
                ret.push_back(matrix[i][j]);
            for(int j = i; j < lastRow; ++j)
                ret.push_back(matrix[j][lastCol]);
            for(int j = lastCol; j > i; --j)
                ret.push_back(matrix[lastRow][j]);
            for(int j = lastRow; j > i; --j)
                ret.push_back(matrix[j][i]);
        }
    }

    return ret;
}



int main()
{
	int m = 3, n = 3;
	vector<vector<int> > nums(m, vector<int>(n, 0));
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
			nums[i][j] = i * 3 + j + 1;
	}
	auto ans = spiral_order(nums);
	vector<int> tgt { 1, 2, 3, 6, 9, 8, 7, 4, 5 };
	bool res = true;
	for(int i = 0; i < tgt.size(); ++i)
		res &= (ans[i] == tgt[i]);
	cout << "Test case 1 returns "
	     << ((ans.size() == tgt.size() && res) ? "True" : "False")
	     << endl;

	return 0;
}











// Given an integer n, generate a square matrix filled with elements from 1 to 
// n^2 in spiral order.
// For example,
// Given n = 3,
// You should return the following matrix:
// [
//    [1, 2, 3],
//    [8, 9, 4],
//    [7, 6, 5]
// ]
//


// Idea:
// Just keep an eye on how many levels you should loop, 
// and each loop's start and end index.
// Also if the n is odd, fill the middle element.
// 


#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > generate_matrix(int n)
{
	vector<vector<int>> ret(n,vector<int>(n, 0));
    int nlvl = n / 2;
    int val = 1;
    for(int i = 0; i < nlvl; ++i)
    {
        int last = n - 1 - i;
        for(int j = i; j < last; ++j) 
            ret[i][j] = val++;
        for(int j = i; j < last; ++j)
            ret[j][last] = val++;
        for(int j = last; j > i; --j)
            ret[last][j] = val++;
        for(int j = last; j > i; --j)
            ret[j][i] = val++;
    }
    if(n % 2 == 1)
        ret[n/2][n/2] = val;
    return ret;
}



int main()
{
	int n = 3;
	auto ans = generate_matrix(n);
	cout << "Test case 1 returns "
	     << ((ans.size() == 3 && 
              ans[0].size() == 3 &&
              ans[0][0] == 1 && ans[0][1] == 2 && ans[0][2] == 3 &&
              ans[1].size() == 3 &&
              ans[1][0] == 8 && ans[1][1] == 9 && ans[1][2] == 4 &&
              ans[0].size() == 3 &&
              ans[2][0] == 7 && ans[2][1] == 6 && ans[2][2] == 5)
              ? "True" : "False")
	     << endl;

	return 0;
}











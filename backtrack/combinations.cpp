// Problem description:
// Given two integers n and k, return all possible combinations of k numbers 
// out of 1 .. n.
// For example,
// If n = 4 and k = 2, a solution is 
// [
//   [2, 4],
//   [3, 4],
//   [2, 3],
//   [1, 2],
//   [1, 3],
//   [1, 4],
// ]
// 
// Idea: Just see the code, you'll get it.

#include <iostream>
#include <vector>

using namespace std;

void find_comb(int n, int start, int k, vector<int>& sol, 
	           vector<vector<int> >& all_sol)
{
	if(k == 0)
	{
		all_sol.push_back(sol);
		return;
	}
	for(int i = start; i <= n - k + 1; ++i)
	{
		sol.push_back(i);
		find_comb(n, i+1, k-1, sol, all_sol);
		sol.pop_back();
	}
}

vector<vector<int> > find_comb(int n, int k)
{
	vector<int> sol;
	vector<vector<int> > all_sol;
	find_comb(n, 1, k, sol, all_sol);
	return all_sol;
}

int main()
{
	int n = 4, k = 2;
	// [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
	auto ans = find_comb(n, k);
	cout << "Test case returns "
	     << ((ans.size() == 6 && 
              ans[0].size() == 2 && ans[0][0] == 1 && ans[0][1] == 2 &&
              ans[1].size() == 2 && ans[1][0] == 1 && ans[1][1] == 3 &&
              ans[2].size() == 2 && ans[2][0] == 1 && ans[2][1] == 4 &&
              ans[3].size() == 2 && ans[3][0] == 2 && ans[3][1] == 3 &&
              ans[4].size() == 2 && ans[4][0] == 2 && ans[4][1] == 4 &&
              ans[5].size() == 2 && ans[5][0] == 3 && ans[5][1] == 4)
              ? "True" : "False")
	     << endl;


	return 0;
}


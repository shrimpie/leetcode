// Problem description:

// Given a set of distinct integers, nums, return all possible subsets.
// Note: The solution set must not contain duplicate subsets.
// For example,
// If nums = [1,2,3], a solution is:
// [
//   [3],
//   [1],
//   [2],
//   [1,2,3],
//   [1,3],
//   [2,3],
//   [1,2],
//   []
// ]

// Idea:
// 1. Use a vector to record each solution, and each time you found one,
//    insert it into the results.
// 2. You also could use bit manipulation.
//    For example, above example can be expressed like this:
//    000 -> [], 100 -> [1], ..., 111 -> [1,2,3]

#include <iostream>
#include <vector>

using namespace std;

void find_subsets(vector<int>& S, int start, vector<int>& sol, 
	              vector<vector<int> >& all_sets)
{
	for(int i = start; i < S.size(); ++i)
	{
		sol.push_back(S[i]);
		all_sets.push_back(sol);
		find_subsets(S, i+1, sol, all_sets);
		sol.pop_back();
	}
}

vector<vector<int> > subsets(vector<int>& S)
{
	vector<vector<int> > all_sets;
	vector<int> sol;
	all_sets.push_back(sol);
	sort(S.begin(), S.end());
	find_subsets(S, 0, sol, all_sets);
	return all_sets;
}

int main()
{
	vector<int> S { 1, 2, 3 };
	auto ans = subsets(S);

	cout << "Test case 1 returns "
	     << ((ans.size() == 8 &&
	     	  ans[0].size() == 0 &&
	     	  ans[1].size() == 1 && ans[1][0] == 1 && 
	     	  ans[2].size() == 2 && ans[2][0] == 1 && ans[2][1] == 2 &&
	     	  ans[3].size() == 3 && ans[3][0] == 1 && ans[3][1] == 2 &&
	     	                        ans[3][2] == 3 &&
	     	  ans[4].size() == 2 && ans[4][0] == 1 && ans[4][1] == 3 &&
	     	  ans[5].size() == 1 && ans[5][0] == 2 &&
	     	  ans[6].size() == 2 && ans[6][0] == 2 && ans[6][1] == 3 &&
	     	  ans[7].size() == 1 && ans[7][0] == 3)
	     	  ? "True" : "False")
	     << endl;

	return 0;
}


// Problem description:

// Given a collection of integers that might contain duplicates, nums, return 
// all possible subsets.
// Note: The solution set must not contain duplicate subsets.
// For example,
// If nums = [1,2,2], a solution is:
// [
//   [2],
//   [1],
//   [1,2,2],
//   [2,2],
//   [1,2],
//   []
// ]

// Idea:
// 1. Use a vector to record each solution, and each time you found one,
//    insert it into the results.

#include <iostream>
#include <vector>

using namespace std;

void find_subsets_with_dup(vector<int>& S, int start, vector<int>& sol, 
	              vector<vector<int> >& all_sets)
{
	for(int i = start; i < S.size(); ++i)
	{
		if(i > start && S[i] == S[i-1])
			continue;
		sol.push_back(S[i]);
		all_sets.push_back(sol);
		find_subsets_with_dup(S, i+1, sol, all_sets);
		sol.pop_back();
	}
}

vector<vector<int> > subsets_with_dup(vector<int>& S)
{
	vector<vector<int> > all_sets;
	vector<int> sol;
	all_sets.push_back(sol);
	sort(S.begin(), S.end());
	find_subsets_with_dup(S, 0, sol, all_sets);
	return all_sets;
}

int main()
{
	vector<int> S { 1, 2, 2 };
	auto ans = subsets_with_dup(S);

	cout << "Test case 1 returns "
	     << ((ans.size() == 6 &&
	     	  ans[0].size() == 0 &&
	     	  ans[1].size() == 1 && ans[1][0] == 1 && 
	     	  ans[2].size() == 2 && ans[2][0] == 1 && ans[2][1] == 2 &&
	     	  ans[3].size() == 3 && ans[3][0] == 1 && ans[3][1] == 2 &&
	     	                        ans[3][2] == 2 &&
	     	  ans[4].size() == 1 && ans[4][0] == 2 &&
	     	  ans[5].size() == 2 && ans[5][0] == 2 && ans[5][1] == 2)
	     	  ? "True" : "False")
	     << endl;

	return 0;
}


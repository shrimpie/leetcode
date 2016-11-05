// Given a set of candidate numbers (C) and a target number (T), find all 
// unique combinations in C where the candidate numbers sum to T. The same 
// repeated number may be chosen from C unlimited number of times.

// The solution set must not contain duplicate combinations.

#include <iostream>
#include <vector>

using namespace std;


void find_combi_sum(vector<int>& candidates, int start, int target, 
	                vector<int>& sol, vector<vector<int> >& all_sol)
{
	if(target == 0)
	{
		all_sol.push_back(sol);
		return;
	}
	for(int i = start; i < candidates.size(); ++i)
	{
		// Skip same numbers
		if(i > start && candidates[i] == candidates[i-1])
			continue;
		if(candidates[i] <= target)
		{
			sol.push_back(candidates[i]);
			find_combi_sum(candidates, i, target - candidates[i], sol,
				           all_sol);
			sol.pop_back();
		}
	}
}

vector<vector<int> > combination_sum(vector<int>& candidates, int target)
{
	vector<vector<int> > all_sol;
	vector<int> sol;
	if(candidates.empty())
		return all_sol;
	sort(candidates.begin(), candidates.end());
	find_combi_sum(candidates, 0, target, sol, all_sol);
	return all_sol;
}


int main()
{
	vector<int> candidates { 2, 3, 6, 7 };
	int target = 7;

	auto ans = combination_sum(candidates, target);
	sort(ans.begin(), ans.end(), 
		 [](vector<int>& a, vector<int>& b) { return a.size() < b.size(); } );
	cout << "Test case 1 returns "
	     << ((ans.size() == 2 && 
	     	  ans[0].size() == 1 && ans[0][0] == 7 &&
	     	  ans[1].size() == 3 && ans[1][0] == 2 && ans[1][1] == 2 && 
	     	                        ans[1][2] == 3) ? "True" : "False")
	     << endl;

	return 0;
}















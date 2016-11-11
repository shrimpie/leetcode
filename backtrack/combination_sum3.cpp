// Problem description:

// Find all possible combinations of k numbers that add up to a number n, given
// that only numbers from 1 to 9 can be used and each combination should be a 
// unique set of numbers.

// Example 1:
// Input: k = 3, n = 7
// Output:
// [[1,2,4]]


#include <iostream>
#include <vector>

using namespace std;


void search(vector<int>& candidates, int target, int i, int &k,
	        vector<vector<int> >& res, vector<int>& sol)
{
	if(target < 0)
		return;
	else
	{
		if(target == 0 && sol.size() == k)
			res.push_back(sol);
		else
		{
			for(int j = i; j < candidates.size(); ++j)
			{
				if(j == 0 || candidates[j] != candidates[j-1])
				{
					sol.push_back(candidates[j]);
					search(candidates, target - candidates[j], j + 1, k, res, sol);
					sol.pop_back();
				}
			}
		}
	}
}

vector<vector<int> > combination_sum3(int k, int target)
{
	vector<vector<int> > res;
	vector<int> sol;
	vector<int> candidates(9);

	for(int i = 1; i <= 9; ++i)
		candidates[i-1] = i;

	search(candidates, target, 0, k, res, sol);

	return res;
}


int main()
{
	int target = 7;
	int k = 3;

	auto ans = combination_sum3(k, target);

	cout << "Test case 1 returns "
	     << ((ans.size() == 1 && 
	     	  ans[0][0] == 1 && ans[0][1] == 2 && ans[0][2] == 4)
	          ? "True" : "False")
	     << endl;

	return 0;
}















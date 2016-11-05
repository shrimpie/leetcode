// Given a collection of numbers that might contain duplicates, return all 
// possible unique permutations.

// For example:
// [1, 1, 2] have the following unique permutations:
// [
//   [1, 1, 2],
//   [1, 2, 1],
//   [2, 1, 1] 
// ]

#include <iostream>
#include <vector>

using namespace std;


// This one differs from permutation version 1 by skipping duplicates. 
void find_permutations_unique(vector<int>& num, vector<bool>& used, 
	                          vector<int>& per, vector<vector<int> >& res)
{
	if( per.size() == num.size())
	{
		res.push_back(per);
		return;
	}
	for(int i = 0; i < num.size(); ++i)
	{
		if(used[i])
			continue;
		if(i > 0 && num[i] == num[i-1] && !used[i-1])
			continue;
		used[i] = true;
		per.push_back(num[i]);
		find_permutations_unique(num, used, per, res);
		per.pop_back();
		used[i] = false;
	}
}

vector<vector<int> > permute_unique(vector<int>& num)
{
	vector<vector<int> > res;
	if(num.empty())
		return res;
	// Sort it first to make duplicate numbers stay adjacent.
	sort(num.begin(), num.end());
	vector<bool> used(num.size(), false);
	vector<int> per;
	find_permutations_unique(num, used, per, res);

	return res;
}


int main()
{

	vector<int> a { 1, 1, 2 };
	auto res = permute_unique(a);
	cout << "Test case 1 returns: "
	<< ((res[0][0] == 1 && res[0][1] == 1 && res[0][2] == 2 &&
	   	 res[1][0] == 1 && res[1][1] == 2 && res[1][2] == 1 &&
	   	 res[2][0] == 2 && res[2][1] == 1 && res[2][2] == 1 ) ? "True" : "False")
	<< endl;

	return 0;
}



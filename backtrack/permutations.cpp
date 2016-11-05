// Given a collection of distinct numbers, return all possible permutations.

#include <iostream>
#include <vector>

using namespace std;


// 
// 
void find_permutations(vector<int>& num, vector<bool>& used, vector<int>& per, 
	                   vector<vector<int> >& res)
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
		used[i] = true;
		per.push_back(num[i]);
		find_permutations(num, used, per, res);
		per.pop_back();
		used[i] = false;
	}
}

vector<vector<int> > permute(vector<int>& num)
{
	vector<vector<int> > res;
	if(num.empty())
		return res;
	vector<bool> used(num.size(), false);
	vector<int> per;
	find_permutations(num, used, per, res);

	return res;
}


int main()
{

	vector<int> a { 1, 2, 3 };
	auto res = permute(a);
	cout << "Test case 1 returns: "
	<< ((res[0][0] == 1 && res[0][1] == 2 && res[0][2] == 3 &&
	   	 res[1][0] == 1 && res[1][1] == 3 && res[1][2] == 2 &&
	   	 res[2][0] == 2 && res[2][1] == 1 && res[2][2] == 3 &&
	   	 res[3][0] == 2 && res[3][1] == 3 && res[3][2] == 1 &&
	   	 res[4][0] == 3 && res[4][1] == 1 && res[4][2] == 2 &&
	   	 res[5][0] == 3 && res[5][1] == 2 && res[5][2] == 1 ) ? "True" : "False")
	<< endl;

	return 0;
}



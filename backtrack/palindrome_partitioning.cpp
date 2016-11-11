// Problem description:
// Given a string s, partition s such that every substring of the partition 
// is a palindrome.
// Return all possible palindrome partition of s.
// For example, given s = "aab",
// Return 
// [
//   ["aa", "b"],
//   ["a", "a", "b"]
// ]

// Idea: BFS + backtracking.
// 1. 
// 2. 



#include <iostream>
#include <vector>

using namespace std;


void find_partitions(string& s, int start, vector<vector<bool> >& is_pal, 
	                 vector<string>& sol, vector<vector<string> >& ret)
{
	if(start == s.size())
	{
		ret.push_back(sol);
		return;
	}

	for(int i = start; i < s.size(); ++i)
	{
		if(is_pal[start][i])
		{
			int len = i - start + 1;
			sol.push_back(s.substr(start, len));
			find_partitions(s, i+1, is_pal, sol, ret);
			sol.pop_back();
		}
	}
}

vector<vector<string> > partition(string s)
{
	int n = s.size();
	vector<vector<string> > ret;
	vector<string> sol;
	vector<vector<bool> > is_pal(n, vector<bool>(n, false));

	for(int i = n - 1; i >= 0; --i)
	{
		for(int j = i; j < n; ++j)
			is_pal[i][j] = ((j - i <= 2 || is_pal[i+1][j-1]) && s[i] == s[j]);
	}
	find_partitions(s, 0, is_pal, sol, ret);

	return ret;
}



int main()
{

	string s = "aab";
	auto ans = partition(s);

	cout << "Test case 1 returns "
	     << ((ans.size() == 2 && 
	     	  ans[0].size() == 3 && ans[0][0] == "a" && ans[0][1] == "a" && 
	     	  ans[0][2] == "b" && 
	     	  ans[1].size() == 2 && ans[1][0] == "aa" && ans[1][1] == "b")
	     	  ? "True" : "False")
	     << endl;




	return 0;
}


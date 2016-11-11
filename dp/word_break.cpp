// Problem description:
// Given a string s and a dictionary of words dict, determine if s can be 
// segmented into a space-separated sequence of one or more dictionary 
// words.

// For example, given
// s = "leetcode",
// dict = ["leet", "code"]
// Return true because "leetcode" can be segmented as "leet code".

// Idea:
// dp[i]: s[0:i-1] can break into words in dict.
// 1. dp[0] = true;
// 2. dp[i] = true iff:
//    a) there exists a k such that 0 <= k <= i-1, and s[k:i-1] exists in dict.
//    b) s[0:k-1] is breakable, that is dp[k] == true.


#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


bool word_break(string s, unordered_set<string> & dict)
{
	vector<bool> dp(s.size() + 1, false);
	dp[0] = true;
	for(int i = 0; i < s.size(); ++i)
	{
		for(int j = i; j >= 0; --j)
		{
			if(dp[j] && dict.count(s.substr(j, i-j+1)))
			{
				dp[i+1] = true;
				break;
			}
		}
	}
	return dp[s.size()];
}





int main()
{
	string s = "leetcode";
	unordered_set<string> dict { "leet", "code" };
	cout << "Test case 1 returns "
	     << (word_break(s, dict) == true ? "True" : "False")
	     << endl;




	return 0;
}


// Problem description:

// Given a string s and a dictionary of words dict, add spaces in s to 
// cunstruct a sentence where each word is a valid dictionary word.
// Return all such possible sentences.

// For example, given
// s = "catsanddog",
// dict = ["cat", "cats", "and", "sand", "dog"].
// A solution is ["cats and dog", "cat sand dog"].
// 

//

// Idea: dp + dfs + backtracking.
// dp[i]: s[0:i-1] can break into words in dict.
// 1. dp[0] = true;
// 2. dp[i] = true iff:
//    a) there exists a k such that 0 <= k <= i-1, and s[k:i-1] exists in dict.
//    b) s[0:k-1] is breakable, that is dp[k] == true.
// 3. Use dfs and backtracking to record the solution.


#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


bool breakable(string& s, unordered_set<string> & dict)
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

void find_word_break(string &s, unordered_set<string> &dict, int start, 
	                 vector<string>& sol, vector<string>& sents)
{
	if(start == s.size() && !sol.empty())
	{
		string tmp = sol[0];
		for(int i = 1; i < sol.size(); ++i)
			tmp.append(" " + sol[i]);
		sents.push_back(tmp);
	}

	string word;
	for(int i = start; i < s.size(); ++i)
	{
		word.push_back(s[i]);
		if(dict.count(word))
		{
			sol.push_back(word);
			find_word_break(s, dict, i+1, sol, sents);
			sol.pop_back();
		}
	}
}



vector<string> word_break(string s, unordered_set<string>& word_dict)
{
	vector<string> sentences;
	vector<string> sol;
	if(breakable(s, word_dict))
		find_word_break(s, word_dict, 0, sol, sentences);
	return sentences;
}



int main()
{
	string s = "catsanddog";
	unordered_set<string> dict { "cat", "cats", "and", "sand", "dog" };

	auto ans = word_break(s, dict);

	cout << "Test case 1 returns "
	     << ((ans.size() == 2 &&
	     	  ans[0] == "cat sand dog" && ans[1] == "cats and dog")
	          ? "True" : "False")
	     << endl;




	return 0;
}


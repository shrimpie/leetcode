// Problem description:

// Given a string s1, we may represent it as a binary tree by partitioning it 
// to two non-empty substrings recursively.

// Idea:
// 1. Recursive
// 2. DP.



#include <iostream>
#include <vector>

using namespace std;

bool is_scramble(string s1, string s2)
{
	if(s1.size() != s2.size())
		return false;
	const int len = s1.size();
	// dp[k][i][j]: indicates the substring of s1 starting from i and 
	//              the substring of s2 starting from j of length k 
	//              can be converted to each other.
	bool dp[len+1][len][len];
	// Initialize the dp value of substring of length 1.
	for(int i = 0; i <= len - 1; ++i)
	{
		for(int j = 0; j <= len - 1; ++j)
			dp[1][i][j] = s1[i] == s2[j] ? true : false;
	}
	// For substring of length k.
	for(int k = 2; k <= len; ++k)
	{
		for(int i = 0; i <= len - k; ++i) // s1 starts from i
		{
			for(int j = 0; j <= len - k; ++j) // s2 starts from j
			{
				dp[k][i][j] = false;
				for(int divlen = 1; divlen < k && !dp[k][i][j]; ++divlen)
					dp[k][i][j] = (dp[divlen][i][j] && dp[k-divlen][i+divlen][j+divlen]) || 
						          (dp[divlen][i][j+k-divlen] && dp[k-divlen][i+divlen][j]);
			}
		}
	}
	return dp[len][0][0];
}



int main()
{
	string s1 = "great", s2 = "rgeat";

	cout << "Test case 1 returns "
	     << (is_scramble(s1, s2) == true ? "True" : "False")
	     << endl;




	return 0;
}


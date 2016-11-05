// Implement wildcard pattern matching with support for '?' and '*'.
// '?' matches any single character.
// '*' matches any sequence of characters (including the empty sequence).

// dp[i][j]: If s[0:i-1] and p[0:j-1] match.
// 1. If s[i-1] == p[j-1] || p[j-1] == '?': dp[i][j] = dp[i-1][j-1],
// 2. If p[j-1] == '*':
//    2.1. Match 0 char: dp[i][j] = dp[i][j-1],
//    2.2. Match 1 char: dp[i][j] = dp[i-1][j-1],
//    2.3. Match > 1 char: dp[i][j] = dp[i-1][j]
//         This last case example: s = "aabcd", p = "aa*d", i = 4, j = 3.
// 

#include <iostream>
#include <vector>

using namespace std;

bool is_match(string s, string p)
{
	int m = s.size(), n = p.size();

	vector<vector<bool> > dp(m+1, vector<bool>(n+1, false));
	dp[0][0] = true;

	for(int i = 0; i <= m; ++i)
	{
		for(int j = 0; j <= n; ++j)
		{
			if(p[j-1] == '?' || (i > 0 && p[j-1] == s[i-1]))
				dp[i][j] = i > 0 && dp[i-1][j-1];
			else if(p[j-1] == '*')
				// '*' can match for more than one char, which makes
				// dp[i][j-1] and dp[i-1][j-1] false, but dp[i-1][j] true. 
				dp[i][j] = dp[i][j-1] || 
			               (i > 0 && (dp[i-1][j-1] || dp[i-1][j]));
			
		}
	}

	return dp[m][n];
}


int main()
{
	string s[] = { "aa", "aa", "aaa", "aa", "aa", "ab", "aab" };
	string p[] = { "a",  "aa", "aa",  "*",  "a*", "?*", "c*a*b" };
	bool tgt[] = { false, true, false, true, true, true, false };
	for(int i = 0; i < sizeof(s)/sizeof(s[0]); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
	     << (is_match(s[i], p[i]) == tgt[i] ? "True" : "False")
	     << endl;
	}

	return 0;
}
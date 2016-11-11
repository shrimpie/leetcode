// Problem description:

// Given a string s, partition s such that every substring of the partition is 
// a palindrome.
// Return the minimum cuts needed for a palindrome partitioning of s.
// For example, given s = "aab",
// Return 1 since the palindrome partitioning ["aa", "b"] could be produced 
// using 1 cut.

// Idea: DP
// dp[i]: the minimum cut of s[0:i-1].
// 1. dp[i] = min(dp[j]) + 1, 0 <= j < i, and s[j:i-1] is palindrome.
// 2. is_pal[i][j] = true if (j-i <= 2 or is_pal[i+1][j-1]) && s[i] == s[j])



#include <iostream>
#include <vector>

using namespace std;



int min_cut(string s)
{
	int n = s.size();
	if(n <= 1)
		return 0;
	vector<vector<bool> > is_pal(n, vector<bool>(n, false));
	for(int i = n - 1; i >= 0; --i)
	{
		for(int j = i; j < n; ++j)
			is_pal[i][j] = ((j - i <= 2 || is_pal[i+1][j-1]) && s[i] == s[j]);
	}

	vector<int> dp(n+1, INT_MAX);
	dp[0] = -1;
	// If s[0:i] is a palindrome, this - 1 makes the minimum cut 0 when j = 0.
	// If s[0:1] is not a palindrome, this makes dp[1] 0, and go on from there.
	for(int i = 1; i <= n; ++i)
	{
		for(int j = i - 1; j >= 0; --j)
		{
			if(is_pal[j][i-1])
				dp[i] = min(dp[i], dp[j] + 1);
		}
	}

	return dp[n];
}




int main()
{

	string s = "aab";
	int cut = min_cut(s);

	cout << "Test case returns "
	     << (cut == 1 ? "True" : "False")
	     << endl;




	return 0;
}


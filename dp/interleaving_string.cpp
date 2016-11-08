// Problem description:
// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
// For example,
// Given:
// s1 = "aabcc",
// s2 = "dbbca",
// When s3 = "aadbbcbcac", return true;
// When s3 = "aadbbbaccc", return false.

// Idea:
// Define dp[i][j]: if s1[0:i-1] and s2[0:j-1] can form s3[0:i+j-1].
// 1. dp[0][j] = dp[0][j-1] && s2[j-1] == s3[j-1],
// 2. dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1],
// 3. dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || 
//               (dp[i][j-1] && s2[j-1] == s3[i+j-1])


#include <iostream>
#include <vector>

using namespace std;

bool is_interleaving(string s1, string s2, string s3)
{
	int n1 = s1.size(), n2 = s2.size();
	vector<vector<bool> > A(n1 + 1, vector<bool>(n2 + 1, false));
	if(n1 + n2 != s3.size())
		return false;
	if(s1.empty() && s2.empty() && s3.empty())
		return true;

	A[0][0] = true;
	for(int i = 1; i <= n1; ++i)
		A[i][0] = (A[i-1][0] && s1[i-1] == s3[i-1]);
	for(int i = 1; i <= n2; ++i)
		A[0][i] = (A[0][i-1] && s2[i-1] == s3[i-1]);

	for(int i = 1; i <= n1; ++i)
	{
		for(int j = 1; j <= n2; ++j)
			A[i][j] = (A[i][j-1] && (s2[j-1] == s3[i+j-1])) ||
		              (A[i-1][j] && (s1[i-1] == s3[i+j-1]));
	}
	return A[n1][n2];
}

int main()
{
	string s1 = "aabcc", s2 = "dbbca";
	string s3 = "aadbbcbcac";

	cout << "Test case 1 returns "
	     << (is_interleaving(s1, s2, s3) == true ? "True" : "False")
	     << endl;

	s3 = "aadbbbaccc";
	cout << "Test case 2 returns "
	     << (is_interleaving(s1, s2, s3) == false ? "True" : "False")
	     << endl;

	return 0;
}


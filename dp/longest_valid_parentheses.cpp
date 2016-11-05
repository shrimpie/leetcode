#include <iostream>
#include <vector>

using namespace std;


// D[i]: the length of longest valid substr ending with s[i-1]
// 1. If s[i-1] = '(', D[i] = 0;
// 2. If s[i-1] = ')', find the index j = i - 2 - D[i-1];
//    [Why this j:    [valid] '(' [valid] ')' _ ]
//    [                        j              i ]
//    If s[j] == '(' and j >= 0, then D[i] = D[i-1] + 2 + D[j];
//    If j < 0 || s[j] == ')', D[i] = 0.

int longest_valid_parentheses(string s)
{
	int n = s.size(), maxlen = 0;
	vector<int> dp(n+1, 0);

	for(int i = 1; i <= n; ++i)
	{
		int j = i - 2 - dp[i-1];
		if(s[i-1] == '(' || j < 0 || s[j] == ')')
			dp[i] = 0;
		else
		{
			dp[i] = dp[i-1] + 2 + dp[j];
			maxlen = max(maxlen, dp[i]);
		}
	}
	return maxlen;
}


int main()
{
	string s = "";
	cout << "Empty string test case returns "
	     << (longest_valid_parentheses(s) == 0 ? "True" : "False") << endl;

	s = ")";
	cout << "Single left paren test case returns "
	     << (longest_valid_parentheses(s) == 0 ? "True" : "False") << endl;

	s = "(";
	cout << "Single right paren test case returns "
	     << (longest_valid_parentheses(s) == 0 ? "True" : "False") << endl;

	s = "()()()(((())()()()()()(";
	cout << "Random parens test case returns "
	     << (longest_valid_parentheses(s) == 14 ? "True" : "False") << endl;


	return 0;
}











// Problem description:
// A message containing letters from A-Z is being encoded to numbers using the
// following mapping:
// 'A' -> 1
// 'B' -> 2
// ...
// 'Z' -> 26
// Given an encoded message containing digits, determine the total number of 
// ways to decode it.

// Idea:
// Assume the decode function is h(). 
// 1. For a single digit X, it can be decoded as h(X) only. 
// 2. For a double digits number XY:
//    a) If XY <= 26, it can be decode as h(X), h(Y), h(XY).
//    b) Otherwise, only h(X), h(Y).
// 
// Define dp[i+1] to be the number of ways to decode string s[0:i].
// 1. dp[0] = 1, dp[1] = 1.
// 2. v = s[i-1]*10 + s[i]:
//    a) v <= 26: dp[i+1] = dp[i] + dp[i-1]
//    b) v > 26: dp[i+1] = dp[i]

// Corner cases:
// 1. Y = 0: you cannot decode h(Y), dp[i+1] = dp[i-1] if XY is valid
// 2. X = 0: you cannot decode h(XY), dp[i+1] = dp[i].

// In summay:
// 1. If 9 < XY <= 26, XY canbe decoded together.
// 2. If Y != '0', Y can be decoded as a single digit.


#include <iostream>
#include <vector>

using namespace std;

int num_decodings(string s)
{
	if(s.empty() || s[0] < '1' || s[0] > '9')
		return 0;

	vector<int> dp(s.size() + 1, 0);
	dp[0] = dp[1] = 1;

	for(int i = 1; i < s.size(); ++i)
	{
		if(!isdigit(s[i]))
			return 0;
		int v = (s[i-1] - '0') * 10 + (s[i] - '0');

		// If v is in range (9,26], you can definitely use s[i-1] and s[i] as a
		// valid char, so at least you can add dp[i-1] times of ways of 
		// decoding, no matter dp[i-1] is valid or not.
		// Example: 
		// 1. If you meet a "30" for current position, you cannot possibly 
		//    decode it. The below addition will be skipped.
		// 2. If you meet a "02" for instance, you can decode it only if you 
		//    can decode the string with current 0.
		if(v <= 26 && v > 9)
			dp[i+1] += dp[i-1];

		// If Y != '0', assuming dp[i] has been assigned the right number of 
		// ways to decode, it might be 0 or a positive number. No matter what, 
		// you are allowed to add it.
		// Case "30" will pass this too, and you get a dp[i+1] == 0.
		if(s[i] != '0')
			dp[i+1] += dp[i];

		// If you cannot decode this thing so far, it must be a invalid string.
		if(dp[i+1] == 0)
			return 0;
	}
	return dp[s.size()];
}



int main()
{
	string s = "123";
	cout << "Test case 1 returns "
	     << (num_decodings(s) == 3 ? "True" : "False")
	     << endl;

	return 0;
}


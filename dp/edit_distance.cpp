// Problem description:
// Given two words word1 and word2, find the minimum number of steps required 
// to convert word1 to word2. (each operation is counted as 1 step)
// You have the following three operations permitted on a word:
// a) Insert a character,
// b) Delete a character,
// c) Replace a character.
//

// Idea:
// DP[i+1][j+1]: edit distane of word1[0:i] -> word2[0:j]
// The formula:
// 1. DP[i+1][j+1] = DP[i+1][j] + 1, (insert one at the end of word1)
// 2. DP[i+1][j+1] = DP[i][j+1] + 1, (delete one at the end of word1)
// 3. DP[i+1][j+1] = DP[i][j] + (word1[i] == word2[j] ? 0 : 1), (replace one)

// Then DP[i+1][j+1] = min(DP[i+1][j] + 1, DP[i][j+1] + 1, DP[i][j] + k),
// k = (word1[i] == word2[j] ? 0 : 1).

// Boundaries:
// DP[i][0] = i: word2 is empty, delete i chars
// DP[0][i] = i: word1 is empty, insert i chars.

#include <iostream>
#include <vector>

using namespace std;


int min_distance(string word1, string word2)
{
    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for(int j = 1; j <= n; ++j)
        dp[0][j] = j;
    
    for(int i = 1; i <= m; ++i)
    {
        dp[i][0] = i;
        for(int j = 1; j <= n; ++j)
        {
            dp[i][j] = dp[i-1][j-1];
            if(word1[i-1] != word2[j-1])
                ++dp[i][j];
            dp[i][j] = min(min(dp[i-1][j] + 1, dp[i][j-1] + 1), dp[i][j]);
        }
    }
    
    return dp[m][n];    
}




int main()
{
	vector<string> word1 { "abshsah", "shoghoaghos", "shoagho" };
	vector<string> word2 { "shoagoso", "shoaghosghoah", "shogaho" };
	vector<int> tgt { 7, 4, 2 };
	for(int i = 0; i < word1.size(); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
	         << (min_distance(word1[i], word2[i]) == tgt[i] ? "True" : "False")
	         << endl;
	}


	return 0;
}


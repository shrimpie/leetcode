// Problem description:
// 
// Find the length of the longest substring T of a given string (consisting of 
// lowercase letters only) such that every character in T appears no less than 
// k times.

// Idea:
// 1. Sliding window to check if current window satisfies the condition.
// 2. An integer to check if every char appears at least k times.



#include <iostream>
#include <vector>

using namespace std;


int longest_substring(string s, int k)
{
	int res = 0, i = 0, n = s.size();
	while(i + k < n)
	{
		// Use a hash table to count each char
		int m[26] = {0}, mask = 0, max_idx = i;
		for(int j = i; j < n; ++j)
		{
			int t = s[j] - 'a';
			++m[t];
			if(m[t] < k)           // s[j] occurs less than k times.
				mask |= (1 << i);  // Set it to 1
			else
				mask &= ~(1 << i); // Otherwise, set it 0.
			if(mask == 0)
			{
				res = max(res, j - i + 1);
				max_idx = j;
			}
		}

		// Why starting from max_idx + 1?
        // Because after max_idx, there gotta be some char c after j that 
        // appears < k time, which makes the whole string not a valid candidate
        // string. If no char after j appears <= k times, then j should be a 
        // larger index, since add the former [i:j] substr would make a longer 
        // valid candidate substr. So, from index less than index j would not 
        // add occurences to the char that appears less than k times, so won't 
        // make a longer valid substr.
		i = max_idx + 1;
	}

	return res;
}





int main()
{
	string s = "aabbddccdd";
	int k = 2;

	cout << "Test case returns "
	     << (longest_substring(s, k) == 10 ? "True" : "False")
	     << endl;




	return 0;
}


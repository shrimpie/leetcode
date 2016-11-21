// Problem description:
// 
// Given a string that consists of only uppercase English letters, you can 
// replace any letter in the string with another letter at most k times. Find 
// the length of a longest substring containing all repeating letters you can 
// get after performing the above operations.

// Note:
// Both the string's length and k will not exceed 10^4.

// Idea:
// 1. Find the longest substr 's' that max_cnt of same chars 'c' in 
//    the substr satisfies (s - max_cnt) >= k, then you can make the other
//    chars to be 'c'.



#include <iostream>
#include <vector>

using namespace std;


int char_replacement(string s, int k)
{
	int res = 0, max_cnt = 0, start = 0;
	vector<int> counts(26, 0);
	for(int i = 0; i < s.size(); ++i)
	{
		// 1. If max_cnt got updated, then you meet a char that 
		//    occurs more often, and can make a new substr candidate.
		// 2. If max_cnt stays the same, you may find a longer substr
		//    by incrementing i.
		max_cnt = max(max_cnt, ++counts[s[i] - 'A']);
		// Iterate until the substr satisfies the 'k' condition.
		while(i - start + 1 - max_cnt > k)
		{
			// Advances start needs update counts of s[start].
			--counts[s[start] - 'A'];
			++start;
		}
		// Until the substr is got, update longest substr len so far.
		res = max(res, i - start + 1);
	}

	return res;
}





int main()
{
	string s = "aabbddccdd";
	int k = 2;

	cout << "Test case returns "
	     << (char_replacement(s, k) == 10 ? "True" : "False")
	     << endl;




	return 0;
}


// Problem description:
// Given a string S and a string T, find the minimum window in S which will 
// contain all the characters in T in complexity O(n).

// For example,
// S = "ADOBECODEBANC",
// T = "ABC"

// Minimum window is "BANC".
// Note if there is no such window in S that covers all characters in T, return
// the empty string "".

// Idea:
// 1. Use hash tables to record occurrences of characters in T.
// 2. Increment/decrement the occurences of each char, to decide a possible window.
// 3. It's better to try an example, then you'll see the pattern.



#include <iostream>
#include <vector>

using namespace std;


string min_window(string S, string T)
{
    if (T.size() == 0 || S.size() == 0)
        return "";

    int count1[256];
	int count2[256];        
    memset(count1, 0, sizeof(count1));
    memset(count2, 0, sizeof(count2));
    
    for(int i = 0; i < T.size(); ++i)
    {
        ++count1[T[i]];    // count1 is used to find each window start.
        ++count2[T[i]];    // count2 is to indicate current char in T.
    }
    
    int count = T.size();  // To find the first window possible.
    
    int start = 0;
    int minSize = INT_MAX;
    int minStart;
    for(int end = 0; end < S.size(); ++end)
    {
        if (count2[S[end]] > 0) // If found a char in S.
        {
        	// Decrement occurrences in count1, before the first window found, 
        	// the occurrences will stay non-negative.
        	// But for the second round and after, it will be decremented to be
        	// negative, indicating the second possible window has covered the 
        	// char too, so it's not the start of next possible window.
        	// When you meet a char within T with 0 occurences after the 1st 
        	// round, then it's definitely the new start.
            --count1[S[end]];

            // This is only for the 1st round to find 1st window.
            if (count1[S[end]] >= 0)
                --count;
        }
        
        if (count == 0) // The first window is found.
        {
            while(true)
            {
                if (count2[S[start]] > 0)
                {
                    // If the new start has a negative occurrences, it means
                    // when you advances to find next possible window, you met
                    // the chars in T again, the above code will decrement it,
                    // so previously met chars won't be the new start.
                    if (count1[S[start]] < 0)
                        ++count1[S[start]];
                    // If it's not negative, then you didn't meet the first one
                    // so far, so it's definitely the new start.
                    else
                        break;
                }
                ++start;
            }
            // Update minimum lengths.
            if (minSize > end - start + 1)
            {
                minSize = end - start + 1;
                minStart = start;
            }
        }
    }
    
    if (minSize == INT_MAX)
        return "";
    
    string ret(S, minStart, minSize);
    
    return ret;
    
}


int main()
{
	string S = "ADOBECODEBANC";
	string T = "ABC";

	cout << "Test case 1 returns "
	     << (min_window(S, T) == "BANC" ? "True" : "False")
	     << endl;

	return 0;
}


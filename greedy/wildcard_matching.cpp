// Implement wildcard pattern matching with support for '?' and '*'.
// '?' matches any single character.
// '*' matches any sequence of characters (including the empty sequence).



#include <iostream>
#include <vector>

using namespace std;

bool is_match(string s, string p)
{
	int star = -1; // If found a '*' before.
	int m = s.size(), n = p.size();
	int i = 0; // To iterate s.
	int si = 0; // Save index i.
	int j = 0; // To iterate p.


	while(i < m)
	{
		// If found a match, go on.
		if(j < n && ((p[j] == '?') || (p[j] == s[i])))
		{
			++i;
			++j;
			continue;
		}
		// If no match, but found a '*', record star and i's position.
		if(j < n && p[j] == '*')
		{
			star = j++;
			si = i;
			continue;
		}
		// If no match and not a '*', check if found one '*' before,
		// if found one, reset j and i.
		if(star != -1)
		{
			j = star + 1;
			i = ++si;
			continue;
		}
		// If found no match, no star before, return false.
		return false;
	}
	// If remaining '*'s there, keep checking.
	while(j < n && p[j] == '*')
		++j;

	// If j reaches the end, then match.
	return j == n;
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
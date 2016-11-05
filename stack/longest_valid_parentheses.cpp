#include <iostream>
#include <stack>

using namespace std;

// 1. When met a '(', insert it.
// 2. When met a ')', check previous one:
//    a) If '(', pop it and update max length
//    b) If not '(', insert it and update current invalid position
//    c) If the stack is empty, it means all chars met so far are valid.
//       Otherwise, the top of the stack indicates last invalid position.
// 
int longest_valid_parentheses(string s)
{
	stack<pair<int, int> > stk;
	// <index, paren type>, 0: '(' and 1: ')'

	int maxlen = 0, curlen = 0;
	for(int i = 0; i < s.size(); ++i)
	{
		if(s[i] == '(')
			stk.push(make_pair(i, 0));
		else
		{
			if(stk.empty() || stk.top().second == 1)
				stk.push(make_pair(i, 1));
			else
			{
				stk.pop();
				if(stk.empty())
					curlen = i + 1;
				else
					curlen = i - stk.top().first;
				maxlen = max(maxlen, curlen);
			}
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

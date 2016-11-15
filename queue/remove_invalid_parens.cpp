// Problem description:
// Remove the minimum number of invalid parentheses in order to make the input 
// string valid. Return all possible results.
// Note: The input string may contain letters other than the parentheses ( and 
// ).
// Examples:
// "()())()" -> ["()()()", "(())()"]
// "(a)())()" -> ["(a)()()", "(a())()"]
// ")(" -> [""]

// Idea:
// 1. See comments in the code.


#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


bool is_valid(string t)
{
	int cnt = 0;
	for(int i = 0; i < t.size(); ++i)
	{
		if(t[i] == '(')
			++cnt;
		if(t[i] == ')' && cnt-- == 0)
			return false;
	}
	return cnt == 0;
}

vector<string> remove_invalid_parentheses(string s)
{
	vector<string> res;
	unordered_map<string, int> visited;
	queue<string> q;
	q.push(s);
	++visited[s];
	bool found = false;

	while(!q.empty())
	{
		s = q.front(); q.pop();

		if(is_valid(s))
		{
			res.push_back(s);
			found = true;
		}

		// If found a valid one, then stop decreasing parens
        // This will guarantee the minimum # of paren elimination. 
		if(found)
			continue;

		for(int i = 0; i < s.size(); ++i)
		{
			if(s[i] != '(' && s[i] != ')')
				continue;
			string t = s.substr(0, i) + s.substr(i+1);
			if(!visited.count(t))
			{
				q.push(t);
				++visited[t];
			}
		}
	}
	return res;
}




int main()
{

	string s = "()())()";
	auto res = remove_invalid_parentheses(s);

	cout << "Test case returns "
	     << ((res.size() == 2 && 
	     	 (res[0] == "(())()" && res[1] == "()()()"))
	     	 ? "True" : "False")
	     << endl;




	return 0;
}


// Problem description:

// Given integers n, return 1 - n in lexicographical order.

// For example, given 13, return: [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9].

// Please optimize your algorithm to use less time and space. The input size 
// may be as large as 5,000,000.


// Idea:
// See comments in the code.


#include <iostream>
#include <vector>

using namespace std;

vector<int> lexico_order(int n)
{
	vector<int> res(n);
	// Always start from 1.
	int cur = 1;
	// 
	for(int i = 0; i < n; ++i)
	{
		res[i] = cur;
		// If cur * 10 <= n, you can always 
		// find the next number by multiplying 10.
		if(cur * 10 <= n)
			cur *= 10;
		else
		{
			// If cur * 10 gets larger than n,
			// first decrease it by dividing by 10.
			if(cur >= n)
				cur /= 10;
			// Now it's valid, keep adding 1
			cur += 1;
			// If met a 0 at end, then get the next 
			// start by removing trailing 0.
			while(cur % 10 == 0)
				cur /= 10;
		}
	}

	return res;
}



int main()
{

	int n = 13;
	auto ans = lexico_order(n);
	bool res = ans.size() == n;
	vector<int> tgt { 1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9 };
	for(int i = 0; i < n; ++i)
		res &= (ans[i] == tgt[i]);

	cout << "Test case 1 returns "
	     << (res ? "True" : "False")
	     << endl;



	return 0;
}


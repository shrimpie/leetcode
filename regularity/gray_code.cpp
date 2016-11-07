// Problem description:
// The gray code is a binary numeral system where two successive values differ 
// in only one bit.
// Given a non-negative integer n representing the total number of bits in the 
// code, print the sequence of gray code. A gray code sequence must begin with
// 0.

// For example, given n = 2, return [0, 1, 3, 2]. Its gray code sequence is:
// 00 - 0
// 01 - 1
// 11 - 3
// 10 - 2

// Note:
// For a given n, a gray code sequence is not uniquely defined.
// For example, [0, 2, 3, 1] is also a valid gray code sequence according to 
// above defintion.

// Idea: find the regularities by list the code.
// n = 0: 0
// n = 1: 0 1
// n = 2: 00, 01, 11, 10 (0, 1, 3, 2)
// n = 3: 000, 001, 011, 010, 110, 111, 101, 100 (0, 1, 3, 2, 6, 7, 5, 4)

// Take n = 3 as an example, the former 4 gray code consists of the code of 
// n = 2, and the last 4 are the reverse of former 4 added 2^2.

// Regularities:
// Gray code of n = i can be formed by including the code of n = i-1, then 
// adding the former one reversely after added 2^(i-1).


#include <iostream>
#include <vector>

using namespace std;

vector<int> gray_code(int n)
{
	vector<int> gray_seq;
	if(n < 0)
		return gray_seq;

	gray_seq.push_back(0);
	int inc = 1;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = gray_seq.size() - 1; j >= 0; --j)
			gray_seq.push_back(gray_seq[j] + inc);
		inc <<= 1;
	}

	return gray_seq;
}


int main()
{
	int n = 2;
	auto ans = gray_code(n);
	cout << "Test case 1 returns "
	     << ((ans.size() == 4 &&
	     	  ans[0] == 0 && ans[1] == 1 && ans[2] == 3 && ans[3] == 2)
	     	  ? "True" : "False")
	     << endl;

	return 0;
}


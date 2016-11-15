// Problem description:
// Given a non-negative integer n, count all numbers with unique digits, x, 
// where 0 <= x < 10^n.

// Example:
// Given n = 2, return 91. (The answer should be the total numbers in the range
// of 0 <= x < 100, excluding [11, 22, 33, 44, 55, 66, 77, 88, 99])

// Idea:
// 1. Use a backtracking approach which contains three states which are 
//    (the current number, number of steps to get that number and a bitmasker
//    which represent which number is marked as visited so far in the current
//    number). Start with state (0, 0, 0) and count all valid number till we 
//    reach number of steps equals to 10^n.
// 2. This problem can also be solved by DP and some knowledge of 
//    combinatorics.
//    a) Let f(k) = count of numbers with unique digits with length equals k
//    b) f(1) = 10, ..., f(k) = 9 * 9 * 8 * (9-k+2). [The first factor is 9 
///      because a number cannot start with 0].



#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int search(int pre, int max, int used)
{
	int res = 0;
	if(pre < max)
		++res;
	else
		return res;
	for(int i = 0; i < 10; ++i)
	{
		if(!(used & (1 << i)))
		{
			used |= (1 << i);
			int cur = 10 * pre + i;
			res += search(cur, max, used);
			used &= ~(1 << i);
		}
	}
	return res;
}

int count_number_with_unique_digits(int n)
{
	int res = 1, max = pow(10, n), used = 0;
	for(int i = 1; i < 10; ++i)
	{
		used |= (1 << i);
		res += search(i, max, used);
		used &= ~(1 << i);
	}
	return res;
}

// combinatorics

int count(int k)
{
	if(k < 1)
		return 0;
	if(k == 1)
		return 10;
	int res = 1;
	for(int i = 9; i >= (11 - k); --i)
		res *= i;
	return res * 9;
}

int count_number_with_unique_digits2(int n)
{
	if(n == 0)
		return 1;
	int res = 0;
	for(int i = 1; i <= n; ++i)
		res += count(i);

	return res;
}






int main()
{

	int n = 2;

	cout << "Test case 1 returns "
	     << (count_number_with_unique_digits(n) == 91 ? "True" : "False")
	     << endl;

	cout << "Test case 2 returns "
	     << (count_number_with_unique_digits2(n) == 91 ? "True" : "False")
	     << endl;



	return 0;
}


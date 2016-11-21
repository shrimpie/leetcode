// Problem description:

// Given integers n and k, find the lexicographically k-th smallest integer in 
// the range from 1 to n.
// Note: 1 <= k <= n <= 10^9
// 
// Example:
// Input:
// n: 13, k: 2

// Output:
// 10
// 
// Explanation:
// The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9],
// so the second smallest number is 10.

// Idea:
// 0. Initialize res = 1, it always starts from 1.
// 1. Count numbers of |{res, res*, res**, res***, ... }|
// 2. If the count cnt is less than k, then skip the current prefix by 
//    incrementing res, and subtract cnt from k;
// 3. Otherwise, cannot skip all, you can skip one by one.



#include <iostream>
#include <vector>

using namespace std;

int find_kth_number(int n, int k)
{
	int res = 1;
	for(--k; k > 0;)
	{
		int cnt = 0;
		for(long long first = static_cast<long long>(res), last = first + 1;
			first <= n; // The interval is not empty
			first *= 10, last *= 10)
		{
			// valid interval = [first, last) union [first, n]
			cnt += static_cast<int>((min(n + 1LL, last) - first)); //
		}

		if(k >= cnt)
		{
			// skip {res, res*, res**, ... }
			++res;
			k -= cnt;
		}
		else
		{
			// not able to skip all, search in more detail
			res *= 10;
			--k;
		}
	}
	return res;
}






int main()
{

	int n = 13, k = 2;

	cout << "Test case 1 returns "
	     << (find_kth_number(n, k) == 10 ? "True" : "False")
	     << endl;
	n = 123455;
	k = 34345;
	cout << "Test case 2 returns "
	     << (find_kth_number(n, k) == 19799 ? "True" : "False")
	     << endl;



	return 0;
}


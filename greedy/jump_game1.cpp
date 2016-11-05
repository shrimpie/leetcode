// Given an array of non-negative integers, you are initially positioned at the
// first index of the array. Each element in the array represents your 
// maximum jump length at that position. Determine if you are able to reach the
// last index.
// For example:
// A = [2,3,1,1,4], return true.
// A = [3,2,1,0,4], return false.


#include <iostream>
#include <vector>

using namespace std;

// Clarification:
// A[i]: the maximum jump length at position i, not that you can only jump once
//       using that length. You can actually reach any position in the range 
//       [i, i + A[i]].

// Greedy style:
// 0. Keep a max_index you can currently reach,
// 1. The condition that you can reach i is i <= max_index,
// 2. Once you reach i, then max_index = max(max_index, i + A[i]),
// 3. The condition that you can reach n-1 is: max_index >= n-1.

bool can_jump(vector<int>& nums)
{
	int n = nums.size();
	int max_index = 0;
	for(int i = 0; i < n; ++i)
	{
		if(i > max_index || max_index >= n-1)
			break;
		max_index = max(max_index, i + nums[i]);
	}
	return (max_index >= n - 1) ? true : false;
}


int main()
{
	vector<int> A { 2, 3, 1, 1, 4 };
	cout << "Test case 1 returns "
	     << (can_jump(A) == true ? "True" : "False")
	     << endl;

	vector<int> B { 3, 2, 1, 0, 4 };
	cout << "Test case 2 returns "
	     << (can_jump(B) == false ? "True" : "False")
	     << endl;


	return 0;
}
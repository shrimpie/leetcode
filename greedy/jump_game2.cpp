// Given an array of non-negative integers, you are initially positioned at the
// first index of the array. Each element in the array represents your 
// maximum jump length at that position. Your goal is to reach the last index 
// in the minimum number of jumps.
// For example:
// A = [2,3,1,1,4], return 2. (Jump 1 step from 0 to 1, then 3 steps to the 
// last.)


#include <iostream>
#include <vector>

using namespace std;

// Clarification:
// A[i]: the maximum jump length at position i, not that you can only jump once
//       using that length. You can actually reach any position in the range 
//       [i, i + A[i]].

// Greedy style:
// 0. Try to calculate the maximum length after jumping k times.
// 1. The formula here: d[k] = max(i + A[i]), d[k-2] < i <= d[k-1].

int jump(vector<int>& nums)
{
	int n = nums.size();
	int cur_max = 0, njumps = 0, i = 0;
	while(cur_max < n - 1)
	{
		int last_max = cur_max;
		for(; i <= last_max; ++i)
			cur_max = max(cur_max, i + nums[i]);
		++njumps;
		if(last_max == cur_max)
			return -1;
	}
	return njumps;
}


int main()
{
	vector<int> A { 2, 3, 1, 1, 4 };
	cout << "Test case 1 returns "
	     << (jump(A) == 2 ? "True" : "False")
	     << endl;

	vector<int> B { 3, 2, 1, 0, 4 };
	cout << "Test case 2 returns "
	     << (jump(B) == -1 ? "True" : "False")
	     << endl;


	return 0;
}
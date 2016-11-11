// Problem description:
// Given an array of n positive integers and a positive integer s, find the 
// minimum length of a subarray of which the sum >= s. If there isn't one, 
// return 0 instead.

// For example, given the array [2,3,1,2,4,3] and s = 7,
// the subarray [4,3] has the minimum length under the problem constraint.

// Idea: similar to sliding window.
// 1. Keep a left pointer and a right one.
// 2. Increment the right one until find the first window.
// 3. Increment the left by one, at the same time update the sum
//    by subtracting the slided-out item.
// 4. If found shorter window, then update minimum value.



#include <iostream>
#include <vector>

using namespace std;


int min_subarray_length(int s, vector<int>& nums)
{
	int n = nums.size();

	int start = 0, end = 0;
	int min = n + 1;
	int sum = 0;
	while(start < n && end < n)
	{
		while(sum < s && end < n)
			sum += nums[end++];

		while(sum >= s && start < end)
		{
			min = (min < end - start ? min : end - start);
			sum -= nums[start++];
		}
	}
	return min == n + 1 ? 0 : min;
}


int main()
{
	int s = 7;
	vector<int> nums { 2,3,1,2,4,3 };

	cout << "Test case 1 returns "
	     << (min_subarray_length(s, nums) == 2 ? "True" : "False")
	     << endl;

	return 0;
}


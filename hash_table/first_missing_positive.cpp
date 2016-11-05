// Given an unsorted array, find the first missing positive integer.
// For example,
// Given [1,2,0] return 3,
// and [3, 4, -1, 1] return 2.


// Idea: Use the array itself as a hash table, and the goal is put every 
//       number i in position i-1, that is, nums[i-1] = i, i = 0 .. n-1.

// Scan each number:
// 1. If nums[i] < 1 or nums[i] > n, it can't be the first missing positive.
// 2. If nums[i] = i + 1, then it is already on the right spot, skip it.
// 3. If nums[i] != i + 1, and 0 < nums[i] <= n, 
//    put nums[i] to nums[nums[i]-1], i.e., swap the two.
// 4. Note to check if nums[i] == nums[nums[i]-1], otherwise, infinite loop.

#include <iostream>
#include <vector>



using namespace std;



int first_missing_positive(vector<int>& nums)
{
	int n = nums.size();
	int i = 0;
	while(i < n)
	{
		if(nums[i] != i + 1 && nums[i] > 0 && nums[i] <= n &&
		   nums[i] != nums[nums[i] - 1])
			swap(nums[i], nums[nums[i] - 1]);
		else
			++i;
	}

	for(int i = 0; i < n; ++i)
	{
		if(nums[i] != i + 1)
			return i + 1;
	}

	return n + 1;
}

int main()
{
	vector<int> nums { 1, 2, 0 };
	cout << "Test case 1 returns "
	     << (first_missing_positive(nums) == 3 ? "True" : "False")
	     << endl;

	vector<int> nums2 { 3, 4, -1, 1 };
	cout << "Test case 2 returns "
	     << (first_missing_positive(nums2) == 2 ? "True" : "False")
	     << endl;

	return 0;
}








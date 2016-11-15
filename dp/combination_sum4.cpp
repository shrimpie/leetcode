// Problem description:

// Given an integer array with all positive numbers and no duplicates, find the
// number of possible combinations that add up to a positive integer target.

// Example:
// nums = [1,2,3]
// target = 4
// The possible combination ways are:
// (1,1,1,1)
// (1,1,2)
// (1,2,1)
// (1,3)
// (2,1,1)
// (2,2)
// (3,1)
//
// Note that different sequences are counted as different combinations.
// Therefore the output is 7.
// 

// Idea:
// dp[i]: the number of possible combinations of target i
// 
// 1. dp[i] = dp[i-x] if i >= x, x belongs to nums.
// 
// 2. If target is much larger than nums' size, you can sort nums, and break
//    when met a i smaller than x in nums, since  dp[i - x] won't make sense, 
//    and for remaining items as well. 
//    

#include <iostream>
#include <vector>

using namespace std;



int combination_sum4(vector<int>& nums, int target)
{
	vector<int> dp(target + 1);
	dp[0] = 1;
	for(int i = 1; i <= target; ++i)
	{
		for(auto a : nums)
		{
			if(i >= a)
				dp[i] += dp[i-a];
		}
	}

	return dp.back();
}

int combination_sum4_2(vector<int>& nums, int target)
{
	vector<int> dp(target + 1);
	dp[0] = 1;
	sort(nums.begin(), nums.end());

	for(int i = 1; i <= target; ++i)
	{
		for(auto a : nums)
		{
			if(i < a)
				break;
			dp[i] += dp[i-a];
		}
	}

	return dp.back();
}


int main()
{

	vector<int> nums { 1, 2, 3 };
	int target = 4;

	cout << "Test case 1 returns "
	     << (combination_sum4(nums, target) == 7 ? "True" : "False")
	     << endl;

	cout << "Test case 2 returns "
	     << (combination_sum4_2(nums, target) == 7 ? "True" : "False")
	     << endl;


	return 0;
}


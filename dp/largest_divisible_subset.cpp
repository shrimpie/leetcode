// Problem description:
// Given a set of distinct positive integers, find the largest subset such that
// every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or 
// Sj % Si = 0.

// If there are multiple solutions, return any subset is fine.

// Example 1:
// nums: [1,2,3]
// Result: [1,2] (of course, [1,3] will also be ok)

// Example 2:
// nums: [1,2,4,8]
// Result: [1,2,4,8]


// Idea:
// dp[i]: the size of largest divisible subset of nums[i:end].
// dp[i] = dp[j] + 1 if nums[j] % nums[i] && dp[i] < dp[j] + 1, for j > i
//   
// 
// 1. Sort the array, compare from last to first
// 2. You also need one more vector to store the previous item that 
//    is divisible by current item.



#include <iostream>
#include <vector>

using namespace std;



vector<int> largest_divisible_subset(vector<int>& nums)
{
	sort(nums.begin(), nums.end());
	vector<int> dp(nums.size(), 0), parent(nums.size(), 0), res;
	int mx = 0, min_idx = 0;

	for(int i = nums.size() - 1; i >= 0; --i)
	{
		for(int j = i; j < nums.size(); ++j)
		{
			if(nums[j] % nums[i] == 0 && dp[i] < dp[j] + 1)
			{
				dp[i] = dp[j] + 1;
				parent[i] = j;
				if(mx < dp[i])
				{
					mx = dp[i];
					min_idx = i;
				}
			}
		}
	}
	for(int i = 0; i < mx; ++i)
	{
		// cout << "min_idx: " << min_idx << endl;
		res.push_back(nums[min_idx]);
		min_idx = parent[min_idx];
	}

	return res;
}




int main()
{
	vector<int> nums { 1, 2, 3, 4 };
	auto ans = largest_divisible_subset(nums);

	cout << "Test case returns "
	     << ((ans.size() == 3 && 
	     	  ans[0] == 1 && ans[1] == 2 && ans[2] == 4)
	     	  ? "True" : "False")
	     << endl;




	return 0;
}


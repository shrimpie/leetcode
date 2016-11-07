// Find the contiguous subarray within an array (containing at least one 
// number), which has the largest sum.
// For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
// the contiguous subarray [4,-1,2,1] has the largest sum = 6.


// Idea:
// 1. dp[i]: the maximum subarray sum ending at A[i].
// 2. The formula: dp[i] = (dp[i-1] < 0) ? dp[i] : dp[i-1] + A[i],
// 3. As dp[i] is determined by dp[i-1] only, so you can use one variable to 
//    save some memory.

#include <iostream>
#include <vector>

using namespace std;


int max_subarray(vector<int>& nums)
{
	int n = nums.size();
	if(n <= 0)
		return 0;
	int max_sum = nums[0], cur_sum = nums[0];
	for(int i = 1; i < n; ++i)
	{
		cur_sum = (cur_sum <= 0) ? nums[i] : nums[i] + cur_sum;
		max_sum = max(max_sum, cur_sum);
	}

	return max_sum;
}

int main()
{
	vector<int> A { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	cout << "Test case 1 returns "
	     << (max_subarray(A) == 6 ? "True" : "False")
	     << endl;

	return 0;
}











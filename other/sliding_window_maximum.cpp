// Problem description:
// Given an array nums, there is a sliding window of size k which is moving 
// from the very left of the array to the very right. You can only see the k 
// numbers in the window. Each time the sliding window moves right by one 
// position.

// For example:
// Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
// Return the max sliding window as [3,3,5,5,6,7].

// Idea:
// 1. Use a deque to store each window's maximum value
// 2. When shifted to a new window, pop the front value of deque
// 3. Inside a window, pop back of the deque if back value is less than 
//    current value.
// 3. Each time add the front value to result.



#include <iostream>
#include <vector>
#include <deque>

using namespace std;


vector<int> max_sliding_window(vector<int>& nums, int k)
{
	vector<int> res;
	deque<int> q;
	for(int i = 0; i < nums.size(); ++i)
	{
		// If q.front() == i - k, then the window got shifted 
        // one step to the right, then the left element got popped out.
        if (!q.empty() && q.front() == i - k)
            q.pop_front();
        
        // Inside the window, keep popping smaller elements.
        while (!q.empty() && nums[q.back()] < nums[i])
            q.pop_back();
        
        // Push in last index.
        q.push_back(i);
        
        // Each window, push in the front element of the dequeue.
        if (i >= k - 1)
            res.push_back(nums[q.front()]);
	}

	return res;
}





int main()
{
	int k = 3;
	vector<int> nums { 1,3,-1,-3,5,3,6,7 };
	auto ans = max_sliding_window(nums, k);
	cout << "Test case 1 returns "
	     << ((ans.size() == 6 && 
	     	  ans[0] == 3 && ans[1] == 3 && ans[2] == 5 &&
	     	  ans[3] == 5 && ans[4] == 6 && ans[5] == 7)
	     	  ? "True" : "False")
	     << endl;




	return 0;
}


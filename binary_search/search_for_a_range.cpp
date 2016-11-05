#include <iostream>
#include <vector>

using namespace std;



int findLeftMost(vector<int>& nums, int n, int target)
{
    int start = 0, end = n - 1;
    while(start <= end)
    {
        int mid = (end + start) / 2;
        // If target is less than or equal to target,
        // keep finding to the left to find the start.
        if(target <= nums[mid])
            end = mid - 1;
        // If target is larger, it must be in the right half.
        else if(target > nums[mid])
            start = mid + 1;
    }
    // If start is at a valid position, return it.
    if(start >= 0 && start < n && nums[start] == target)
        return start;
    return -1;
}

int findRightMost(vector<int>& nums, int n, int target)
{
    int start = 0, end = n - 1;
    while(start <= end)
    {
        int mid = (end + start) / 2;
        if(target < nums[mid])
            end = mid - 1;
        else if(target >= nums[mid])
            start = mid + 1;
    }
    if(end >= 0 && end < n && nums[end] == target)
        return end;
    return -1;
}

vector<int> searchRange(vector<int>& nums, int target)
{
    vector<int> range;
    range.push_back(findLeftMost(nums, nums.size(), target));
    range.push_back(findRightMost(nums, nums.size(), target));
    return range;
}


int main()
{
	int target = 5;
	vector<int> nums { 1, 2, 3, 4, 5, 5, 5, 5, 6, 7, 8 };
	auto res = searchRange(nums, target);

	cout << "Search range in nums returns "
	     << ((res[0] == 4 && res[1] == 7) ? "True" : "False") << endl;


	return 0;
}




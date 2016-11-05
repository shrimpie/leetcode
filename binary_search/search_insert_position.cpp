// Given a sorted array and a target value, return the index if the target is 
// found. If not, return the index where it would be if it were inserted in 
// order.

#include <iostream>
#include <vector>

using namespace std;

int search_insert(vector<int>& nums, int target)
{
	int start = 0, end = nums.size() - 1;
	while(start <= end)
	{
		int mid = (end + start) / 2;
        if(target == nums[mid]) 
            return mid;
        else if(target < nums[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }

    // If the target is not found, 
    // start is exactly the position to insert.
    return start;
}

int main()
{
	int target = 8;
	vector<int> nums { 1, 2, 3, 4, 5, 6, 7, 9 };

	cout << "Insert position test case 1 returns "
	     << (search_insert(nums, target) == 7 ? "True" : "False") << endl;

	return 0;
}



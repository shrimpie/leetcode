#include <iostream>
#include <vector>


using namespace std;

int search(vector<int>& nums, int n, int target)
{
	int start = 0, end = n - 1;
	while(start <= end)
	{
		// cout << "start: " << start << endl;
		// cout << "end: " << end << endl;

		int mid = start + (end - start) / 2;
		if(nums[mid] == target)
			return mid;
		if(nums[mid] < nums[end]) // Right half sorted.
		{
			if(target > nums[mid] && target <= nums[end])
				start = mid + 1;
			else
				end = mid - 1;
		}
		else                      // Left half sorted.
		{
			if(target >= nums[start] && target < nums[mid])
				end = mid - 1;
			else
				start = mid + 1;
		}
	}

	return -1;
}

int search(vector<int>& nums, int target)
{
	if(nums.empty())
		return -1;
	return search(nums, nums.size(), target);
}



int main()
{
	int target = 5;
	vector<int> nums1 {};
	cout << "Empty nums array test case returns "
         << (search(nums1, target) == -1 ? "True" : "False") << endl;

    int arr1[] = { 8, 9, 1, 2, 3, 4, 6, 7 };
    vector<int> nums2(begin(arr1), end(arr1));

    cout << "Nums array without target test case returns "
         << (search(nums2, target) == -1 ? "True" : "False") << endl;

    int arr2[] = { 8, 9, 1, 2, 3, 4, 5, 6, 7 };
    vector<int> nums3(begin(arr2), end(arr2));
    cout << "Nums array with target test case returns "
         << (search(nums3, target) == 6 ? "True" : "False") << endl;


	return 0;
}
// Problem description:

// Find the kth largest element in an unsorted array. Note that it is the kth 
// largest element in the sorted order, not the kth distinct element.

// For example,
// Given [3,2,1,5,6,4] and k = 2, return 5.

// Note:
// You may assume k is always valid, 1 <= k <= array's length.



#include <iostream>
#include <vector>

using namespace std;

void downshift(vector<int>& h, int n, int parent)
{
	if(parent < 0)
		return;
	int left = 2 * parent + 1;
	int right = 2 * parent + 2;
	int mxch;
	if(left >= n)
		return;
	if(right >= n)
		mxch = left;
	else
		mxch = h[left] >= h[right] ? left : right;

	if(h[parent] < h[mxch])
	{
		swap(h[parent], h[mxch]);
		downshift(h, n, mxch);
	}
}

void build_heap(vector<int> &h, int n)
{
	// The -1 is because the heap uses the first index 0.
	int parent = n / 2 - 1;
	for(; parent >= 0; --parent)
		downshift(h, n, parent);
}


void heapsort(vector<int> &h, int n)
{
	build_heap(h, n);
	int i = n - 1;
	vector<int> b(n, 0);
	// Use another vector b to store the sorted elements.
	while(i >= 0)
	{
		// Get the largest one.
		b[n-i-1] = h[0];
		// swap the first with current last one.
		swap(h[0], h[i]);
		// Down shift to get the largest float to the top.
		downshift(h, i, 0);
		// Go to next round
		--i;
	}
	// Now b is the sorted vector
	for(int i = 0; i < n; ++i)
		h[i] = b[i];

}



int find_kth_largest(vector<int>& nums, int k)
{
	heapsort(nums, nums.size());
	return nums[k-1];
}


int main()
{

	vector<int> nums { 3, 2, 1, 5, 6, 4 };
	int k = 2;

	cout << "Test case 1 returns "
	     << (find_kth_largest(nums, k) == 5 ? "True" : "False")
	     << endl;




	return 0;
}


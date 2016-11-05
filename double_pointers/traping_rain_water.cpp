// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it is able to trap after raining.
// For example,
// Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
// The figure is omitted here.


// Idea:
// For position i, the trapped water above i is determined by the highest bar 
// on the left and right: height[left] = max{ height[j], j<i }, height[right] =
// max{ height[j], j>i }. Define min_height = min(height[left], height[right]),
// then the trapped water W:
// If min_height <= height[i], W = 0;
// If min_height > height[i], W = min_height - height[i].

#include <iostream>
#include <vector>

using namespace std;

int trap(vector<int>& height)
{
	int n = height.size();
	if(n < 3)
		return 0;
	vector<int> left_height(n, 0);
	vector<int> right_height(n, 0);
	int water = 0;

	for(int i = 1; i < n; ++i)
		left_height[i] = max(left_height[i-1], height[i-1]);

	for(int i = n - 2; i >=0; --i)
	{
		right_height[i] = max(right_height[i+1], height[i+1]);
		int min_height = min(left_height[i], right_height[i]);
		if(min_height > height[i])
			water += min_height - height[i];
	}

	return water;
}


int main()
{
	vector<int> height { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
	cout << "Test case 1 returns "
	     << (trap(height) == 6 ? "True" : "False")
	     << endl;

	return 0;
}
// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it is able to trap after raining.
// For example,
// Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
// The figure is omitted here.

// Idea:
// To trap water, there must exists a shape like a cup, where the middle is
// lower than its two sides. The goal is to find a increasing sequence after 
// a decreasing sequence. As the water can be calculated only when the bar 
// increases, and the calculation needs the bar heights of decreasing 
// sequences. So the decreasing sequence must be cached somehow. Here uses 
// stack. To ease the calculation of the area (i.e., water) width, the value 
// stored in the cache are not the heights of the bars, but the coordinates of
// each bar instead.


#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int trap(vector<int>& height)
{
	int n = height.size();
	if(n < 3)
		return 0;
	stack<int> s;
	s.push(0);
	int water = 0;

	for(int i = 1; i < n; ++i)
	{
		if(height[i] > height[s.top()])
		{
			// Get current bottom.
			int bottom = height[s.top()];
			s.pop();
			// If right bar is higher, use left bar (i.e., at the stack top now)
			// to calculate the water left bar can trap at its level.
			while(!s.empty() && height[i] >= height[s.top()])
			{
				// area: height * width
				water += (height[s.top()] - bottom) * (i - s.top() - 1);
				// Get the next left bar height.
				bottom = height[s.top()];
				s.pop();
			}
			// The right bar may be low than the left one, 
			// above loop will terminate, still got some water to add.
			// Remaining water can be calculated in the next loop,
			// if there is even higher right bar.
			// No need to worry about it for now.
			if(!s.empty())
				water += (height[i] - bottom) * (i - s.top() - 1);
		}
		// Push previous bar index.
		s.push(i);
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
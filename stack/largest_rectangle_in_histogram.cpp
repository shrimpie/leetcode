// Problem description:
// Given n non-negative integers representing the histogram's bar height where 
// the width of each bar is 1, find the area of largest rectangle in the 
// histogram.

//             6
//           5 _
//           _| |
//          |/|/|  3
//       2  |/|/|2 _
//       _ 1|/|/|_| |
//      | |_|/|/| | |
//     _|_|_|/|/|_|_|_
// 
// Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
// The largest rectangle is shown in the shaded area, which has area = 10 unit.
// 
// For example, 
// Given heights = [2,1,5,6,2,3],
// return 10.
//


// Idea:
// 1. 
// 2. 



#include <iostream>
#include <vector>
#include <stack>

using namespace std;


int largest_rectangle_area(vector<int>& height)
{
	if(height.empty())
		return 0;

	height.push_back(-1);
	height.insert(height.begin(), -1);
	// The two -1s at both ends are to indicate boundaries.
	// And also are used to find the largest possible rectangle.

	stack<int> s;
	int max_area = 0;

	for(int i = 0; i < height.size(); ++i)
	{
		// When found a decreasing pair, start to calculate area.
		while(!s.empty() && height[i] <= height[s.top()])
		{
			// Get current height on top (which is the highest for now)
			int h = height[s.top()];
			// You pop it so the stack top now indicates the previous bar index.
			// The index is used to measure width.
			s.pop();

			// If current height less than the cached heights,
			// You got a possible larger area, update it.
			if(height[i] < h)
				// Area = width * height.
				max_area = max(max_area, (i - s.top() - 1) * h);
		}
		// Try to find an increasing sequence.
		// Cache the indexes in the stack.
		s.push(i);
	}

	// Reset height.
	height.erase(height.begin());
	height.pop_back();

	return max_area;
}





int main()
{
	vector<int> height { 2, 1, 5, 6, 2, 3 };

	cout << "Test case 1 returns "
	     << (largest_rectangle_area(height) == 10 ? "True" : "False")
	     << endl;

	return 0;
}


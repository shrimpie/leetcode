// Problem description:
// A city's skyline is the outer contour of the silhouette formed by all the 
// buildings in that city when viewed from a distance. Now suppose you are 
// given the locations and height of all the buildings as shown on a cityscape 
// photo, write a program to output the skyline formed by these buildings 
// collectively.

// The geometric information of each building is represented by a triplet of 
// integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and
// right edge of the ith building, respectively, and Hi is its height. It is 
// guaranteed that 0 <= Li, Ri <= INT_MAX, 0 < Hi <= INT_MAX, and Ri - Li > 0. 
// You may assume all buildings are perfect rectangles grounded on an 
// absolutely flat surface at height 0.

// For instance, the dimensions of all buildings in Figure A are recorded as: 
// [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ].

// The output is a list of "key points" (red dots in Figure B) in the format of
// [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key
// point is the left endpoint of a horizontal line segment. Note that the last 
// key point, where the rightmost building ends, is merely used to mark the 
// termination of the skyline, and always has zero height. Also, the ground in 
// between any two adjacent buildings should be considered part of the skyline 
// contour.

// For instance, the skyline in Figure B should be represented as: 
// [ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

// Notes:

// * The number of buildings in any input list is guaranteed to be in the range 
//   [0, 10000].
// * The input list is already sorted in ascending order by the left x position
//   Li.
// * The output list must be sorted by the x position.
// * There must be no consecutive horizontal lines of equal height in the 
//   output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] 
//  is not acceptable; the three lines of height 5 should be merged into one in
//  the final output as such: [...[2 3], [4 5], [12 7], ...]

// 
// Idea:
// 0. Split each triplet [l, r, h] to [l, -h] and [r, h]. The negated h is to 
//    indicate a left corner.
// 1. Sort the coordinates by their x coordinates, and each time get the 
//    x coordinates and insert left corner heights (negated again to make it 
//    right), and erase right corner's height. Compare previous highest height
//    with current one, if they differ, then you found a tuning point.
// 2. The reasoning is shown as comments. If it's hard to understand, please 
//    run an example.



#include <iostream>
#include <vector>
#include <set>


using namespace std;


vector<pair<int, int>> get_skyline(vector<vector<int>>& buildings)
{
    vector<pair<int, int>> height;
    for (auto &b : buildings) {
        height.push_back({b[0], -b[2]});
        height.push_back({b[1], b[2]});
    }
    sort(height.begin(), height.end());
    multiset<int> heap;
    // elements in multiset are in order.
    heap.insert(0);
    vector<pair<int, int>> res;
    int pre = 0, cur = 0;
    for (auto &h : height)
    {
        // Met left corner
        if (h.second < 0)
            heap.insert(-h.second);
        else // If met right corner, erase its height.
            heap.erase(heap.find(h.second));
        // Get current largest height .
        cur = *heap.rbegin();
        
        // If current height != previous height,
        // then found a turning point.
        
        // Why?
        // 1. For left corners, it is easier to think through.
        //    a) Because corners with same x but higher height got sorted in 
        //       the multiset. *rbegin() got the smallest one, since left 
        //       corner's height got negated, then it's the heighest. Other 
        //       lower heights just got ignored. Only the top turning point 
        //       got recorded.
        //    b) For corners with different x, they got sorted by their left 
        //       x's, only when met higher heights, there will be a turning 
        //       point, given no right corner has not shown up.
        // 
        // 2. For right corners.
        //    When met a right corner, its height got erased. 
        //    a) If its height is the previous highest, then pre != cur, and 
        //       a turning point must show up.
        //       Why? Because if it's not a turning point, then it must be 
        //       covered by other buildings,
        //       then it's not previous highest building. The right corner's 
        //       x and current highest height will be the turning point.
        //    b) If it is not previous highest, then cur == pre, meaning there 
        //       is one building covering it.
        //       Why? If there is no building covering it, then a right corner 
        //       with smaller x and higher height will be in front of this 
        //       right corner. If that's the case, then that right corner will 
        //       be handled first, and it height will be erased. Until all 
        //       previous height got erase, then will current right corner 
        //       become a turning point. 
        // 
        if (cur != pre)
        {
            res.push_back({h.first, cur});
            pre = cur;
        }
    }
    return res;
            
}





int main()
{

	vector<vector<int> > heights { {2, 9, 10}, {3, 7, 15},  {5, 12, 12},
	                               {15, 20, 10}, {19, 24, 8} };
	auto ans = get_skyline(heights);

	vector<pair<int, int> > tgt;
	tgt.push_back(make_pair(2,10));
	tgt.push_back(make_pair(3,15));
	tgt.push_back(make_pair(7,12));
	tgt.push_back(make_pair(12,0));
	tgt.push_back(make_pair(15,10));
	tgt.push_back(make_pair(20,8));
	tgt.push_back(make_pair(24,0));

	bool res = ans.size() == tgt.size();

	for(int i = 0; i < ans.size(); ++i)
		res &= (ans[i].first == tgt[i].first && ans[i].second == tgt[i].second);

	cout << "Test case returns "
	     << (res == true ? "True" : "False")
	     << endl;




	return 0;
}


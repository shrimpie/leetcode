// Problem description:
// Given a set of non-overlapping intervals, insert a new interval into the 
// intervals (merge if necessary).
// You may assume that the intervals were initially sorted according to their 
// start times.
// 
// Example 1:
// Given [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

// Example 2:
// Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as 
// [1,2],[3,10],[12,16].



// Idea:
// 1. Just remember how to check if two intervals overlap, then you are good
//    to go.



#include <iostream>
#include <vector>

using namespace std;

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

// struct comp_interval{
// 	bool operator()(const Interval &a, const Interval &b) const {
// 		return a.start < b.start;
// 	}
// };

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
{
	vector<Interval> ret;
    bool hasInsert = false;
    
    for(int i = 0; i < intervals.size(); ++i)
    {
        // already insert newInterval
        if(hasInsert)
        {  
            ret.push_back(intervals[i]);
            continue;
        }
        
        // Insert newInterval before current interval
        if(newInterval.end < intervals[i].start)
        {  
            ret.push_back(newInterval);
            ret.push_back(intervals[i]);
            hasInsert = true;
            continue;
        }
        
        // Combine newInterval with current interval
        if(newInterval.start <= intervals[i].end && intervals[i].start <= newInterval.end)
        {
            newInterval.start = min(newInterval.start, intervals[i].start);
            newInterval.end = max(newInterval.end, intervals[i].end);
            continue;
        }
        
        // newInterval after current interval
        ret.push_back(intervals[i]);
    }
    
    if(!hasInsert)
        ret.push_back(newInterval);

	return ret;
}


int main()
{
	vector<Interval> intervals;
	intervals.push_back(Interval(1,3));
	intervals.push_back(Interval(6,9));

	Interval newInterval(2,5);

	auto res = insert(intervals, newInterval);
	cout << "Test case 1 returns: "
	     << ((res.size() == 2 &&
              res[0].start == 1 && res[0].end == 5 &&
              res[1].start == 6 && res[1].end == 9) ? "True" : "False")
	     << endl;

// [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as 
// [1,2],[3,10],[12,16].

	intervals.clear();
	intervals.push_back(Interval(1,2));
	intervals.push_back(Interval(3,5));
	intervals.push_back(Interval(6,7));
	intervals.push_back(Interval(8,10));
	intervals.push_back(Interval(12,16));

	Interval newInterval2(4,9);

	res = insert(intervals, newInterval2);
	cout << "Test case 2 returns: "
	     << ((res.size() == 3 &&
              res[0].start == 1 && res[0].end == 2 &&
              res[1].start == 3 && res[1].end == 10 && 
              res[2].start == 12 && res[2].end == 16) ? "True" : "False")
	     << endl;

	

	return 0;
}


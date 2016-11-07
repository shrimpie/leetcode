// Problem description:
// Given a collection of intervals, merge all overlapping intervals.
// For example,
// Given [1,3],[2,6],[8,10],[15,18],
// return [1,6],[8,10],[15,18].

// Idea:
// 1. Sort the intervals by `start` first.
// 2. If two intervals don't overlap, push it back. 
// 3. If overlap, merge to the previous one.



#include <iostream>
#include <vector>

using namespace std;

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

struct comp_interval{
	bool operator()(const Interval &a, const Interval &b) const {
		return a.start < b.start;
	}
};

vector<Interval> merge(vector<Interval> &intervals)
{
	sort(intervals.begin(), intervals.end(), comp_interval());
	vector<Interval> ret;
	for(int i = 0; i < intervals.size(); ++i)
	{
		if(ret.empty() || ret.back().end < intervals[i].start)
			ret.push_back(intervals[i]);
		else
			ret.back().end = max(ret.back().end, intervals[i].end);
	}

	return ret;
}


int main()
{
	vector<Interval> intervals;
	intervals.push_back(Interval(1,3));
	intervals.push_back(Interval(2,6));
	intervals.push_back(Interval(8,10));
	intervals.push_back(Interval(15,18));

	auto res = merge(intervals);
	cout << "Test case 1 returns: "
	     << ((res.size() == 3 &&
              res[0].start == 1 && res[0].end == 6 &&
              res[1].start == 8 && res[1].end == 10 &&
              res[2].start == 15 && res[2].end == 18) ? "True" : "False")
	     << endl;

	return 0;
}


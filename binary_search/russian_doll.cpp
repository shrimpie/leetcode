// Problem description:
// You have a number of envelopes with widths and heights given as a pair of 
// integers (w, h). One envelope can fit into another if and only if both the 
// width and height of one envelope is greater than the width and height of the
// other envelope.
// What is the maximum number of envelopes can you Russian doll? (put one inside
// the other)

// Example:
// Given envelopes = [[5,4], [6,4], [6,7], [2,3]], the maximum number of 
// envelopes you can Russian doll is 3 ([2,3]=>[5,4]=>[6,7]).


// Idea:
// 1. Sort the envelopes ascending on width and descending on heights.
// 2. Then search the longest increasing subsequence on heights.


#include <iostream>
#include <vector>

using namespace std;


int max_envelopes(vector<pair<int, int> > &envelopes)
{
	sort(envelopes.begin(), envelopes.end(), 
		 [](const pair<int, int>& i, const pair<int, int>& j){
		 	if(i.first == j.first) return i.second > j.second;
		 	return i.first < j.first;
		 });
	vector<int> dp;
	for(int i = 0; i < envelopes.size(); ++i)
	{
		// lower_bound returns the position of first item that's not less than the 
        // item given.
		auto iter = lower_bound(dp.begin(), dp.end(), envelopes[i].second);
		if(iter == dp.end())
		{
			// This is obvious, met item higher than all of the items found so
            // far, append it at the end.
			dp.push_back(envelopes[i].second);
		}
		else
		{
			// This is somewhat tricky, since you found an item in dp
            // that's not less than the new met item enve[i].second,
            // If you change the one in dp to be enve[i].second, it becomes
            // smaller, and it allows new possible greater items to be added,
            // but with old item value, this will not work, at the same time,
            // you updated the item's value, you didn't decrease the length
            // of longest increasing subsequence. But notice the item in the 
            // dp array may not be the `real` sequence. But the length is right.
			*iter = envelopes[i].second;
		}
	}
	return dp.size();
}





int main()
{

	vector<pair<int, int> > envelopes;
	envelopes.push_back(make_pair(5,4));
	envelopes.push_back(make_pair(6,4));
	envelopes.push_back(make_pair(6,7));
	envelopes.push_back(make_pair(2,3));

	cout << "Test case 1 returns "
	     << (max_envelopes(envelopes) == 3 ? "True" : "False")
	     << endl;




	return 0;
}


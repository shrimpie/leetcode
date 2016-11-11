// Problem description:

// There are a total of n courses you have to take, labeled from 0 to n - 1.
// Some courses may have prerequisites, for example to take course 0 you have 
// first to take course 1, which is expressed as a pair: [0,1].
// Given the total number of courses and a list of prerequisite pairs, return 
// the ordering of courses you should take to finish all courses.

// For example:
// 1. 2, [[1,0]]
//   There are a total of 2 courses to take. To take course 1 you should have 
//   finished course 0. So the order is [0,1].
// 2. 4, [[1,0],[2,0], [3,1], [3,2]]
//   This case returns [0,1,2,3] or [0,2,1,3].

// Idea:
// 1. BFS to check in degrees of each node.
// 2. Use stack to cache the ordering.


#include <iostream>
#include <vector>
#include <queue>

using namespace std;



// BFS

vector<int> find_order(int num_courses, vector<pair<int, int> >& prerequisites)
{
	vector<int> res;
	vector<vector<int> > graph(num_courses, vector<int>(0));
	vector<int> in(num_courses, 0);
	for(auto &a : prerequisites)
	{
		graph[a.second].push_back(a.first);
		++in[a.first];
	}

	queue<int> q;
	for(int i = 0; i < num_courses; ++i)
	{
		if(in[i] == 0)
			q.push(i);
	}

	while(!q.empty())
	{
		int t = q.front();
		res.push_back(t);
		q.pop();
		for(auto &a : graph[t])
		{
			--in[a];
			if(in[a] == 0)
				q.push(a);
		}
	}

	if(res.size() != num_courses)
		res.clear();
	
	return res;
}

int main()
{

	int num_courses = 2;
	vector<pair<int, int> > prerequisites;
	prerequisites.push_back(make_pair(1, 0));
	auto ans = find_order(num_courses, prerequisites);

	cout << "Test case 1 returns "
	     << ((ans.size() == 2 && ans[0] == 0 && ans[1] == 1)
	          ? "True" : "False")
	     << endl;

	prerequisites.push_back(make_pair(2,0));
	prerequisites.push_back(make_pair(3,1));
	prerequisites.push_back(make_pair(3,2));
	num_courses = 4;
	ans = find_order(num_courses, prerequisites);
	cout << "Test case 2 returns "
	     << ((ans.size() == 4 && 
	     	  ans[0] == 0 && ((ans[1] == 1 && ans[2] == 2) || 
	     	  	              (ans[1] == 2 && ans[2] == 1)) &&
	     	  ans[3] == 3)
	          ? "True" : "False")
	     << endl;

	return 0;
}


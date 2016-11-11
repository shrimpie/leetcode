// Problem description:
// There are a total of n courses you have to take, labeled from 0 to n - 1.
// Some courses may have prerequisites, for example to take course 0 you have 
// first to take course 1, which is expressed as a pair: [0,1].
// Given the total number of courses and a list of prerequisite pairs, is it 
// possible for you to finish all courses?

// For example:
// 1. 2, [[1,0]]
//   There are a total of 2 courses to take. To take course 1 you should have 
//   finished course 0. So it is possible.
// 2. 2, [[1,0],[0,1]]
//   This case is not possible, since there is a cycle.

// Idea:
// 1. BFS to check in degrees of each node.
// 2. DFS to check if a cycle exists.



#include <iostream>
#include <vector>
#include <queue>

using namespace std;



// BFS

bool can_finish(int num_courses, vector<pair<int, int> >& prerequisites)
{
	vector<vector<int> > graph(num_courses, vector<int>(0));
	vector<int> in(num_courses, 0);
	for(auto a : prerequisites)
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
		q.pop();
		for(auto a : graph[t])
		{
			--in[a];
			if(in[a] == 0)
				q.push(a);
		}
	}

	for(int i = 0; i < num_courses; ++i)
	{
		if(in[i])
			return false;
	}
	
	return true;
}

// DFS
bool can_finish_graph(vector<vector<int> >& graph, vector<int>& visit, int i)
{
	if(visit[i] == -1)
		return false;
	if(visit[i] == 1)
		return true;

	visit[i] = -1;
	for(auto a : graph[i])
	{
		if(!can_finish_graph(graph, visit, a))
			return false;
	}
	visit[i] = 1;

	return true;
}

bool can_finish2(int num_courses, vector<pair<int, int> >& prerequisites)
{
	vector<vector<int> > graph(num_courses, vector<int>(0));
	vector<int> visit(num_courses, 0);
	// 0: unvisited, -1: visiting, 1: visited and fine.
	for(auto a : prerequisites)
		graph[a.second].push_back(a.first);

	for(int i = 0; i < num_courses; ++i)
		if(!can_finish_graph(graph, visit, i))
			return false;

	return true;
}

int main()
{

	int num_courses = 2;
	vector<pair<int, int> > prerequisites;
	prerequisites.push_back(make_pair(1, 0));

	cout << "Test case 1 returns "
	     << (can_finish(num_courses, prerequisites) == true ? "True" : "False")
	     << endl;

	cout << "Test case 2 returns "
	     << (can_finish2(num_courses, prerequisites) == true ? "True" : "False")
	     << endl;

	prerequisites.push_back(make_pair(0,1));
	cout << "Test case 3 returns "
	     << (can_finish(num_courses, prerequisites) == false ? "True" : "False")
	     << endl;

	cout << "Test case 4 returns "
	     << (can_finish2(num_courses, prerequisites) == false ? "True" : "False")
	     << endl;

	return 0;
}


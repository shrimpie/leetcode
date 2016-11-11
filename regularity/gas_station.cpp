// Problem description:
// There are N gas stations along a circular route, where the amount of gas at 
// station i is gas[i].
// You have a car with an unlimited gas tank and it costs cost[i] of gas to 
// travel from station i to its next station (i+1). You begin the journey with 
// empty tank at one of the gas stations.
// Return the starting gas station's index if you can travel around the circuit
// once, otherwise, return -1.

// Note: the solution is guaranteed to be unique.

// Idea:
// 1. If gas[i] < cost[i], i cannot the starting index.
// 2. If sum(gas[i] - cost[i]) < 0, you cannot travel around the circuit.
// 3. For any station i, if start from i, you can travel around the circuit, 
//    then you can reach every gas station. Obviously.
// 4. If this i is unique, then there's no other j such that j != i and from j 
//    you can reach i.
//    [From j if you can reach i, then you can reach any station, paradox.]
// 5. If i is the final start index, then from 0 .. i-1, you cannot reach i.

// Thus the algorithm:
// A) If(sum(gas[i] - cost[i] < 0)), then no such index; otherwise, go to B.
// B) Calculated sum(gas[i] - cost[i]) from index 0, if met an i1 such that 
//    sum < 0, then 0 .. i1-1 are not correct starting index, set i1 to be next
//    possible starting index. Also set sum = 0.
// C) Repeat B, until you meet some ik such that, start from ik you can reach 
//    ik+1..n-1



#include <iostream>
#include <vector>

using namespace std;

int can_complete_circuit(vector<int>& gas, vector<int>& cost)
{
	int start = 0, net_sum = 0, cur_sum = 0;
	for(int i = 0; i < cost.size(); ++i)
	{
		net_sum += gas[i] - cost[i];
		cur_sum += gas[i] - cost[i];
		if(cur_sum < 0)
		{
			start = i + 1;
			cur_sum = 0;
		}
	}
	if(net_sum < 0)
		return -1;
	return start;
}


int main()
{
	vector<int> gas { 2, 3, 4, 3, 5, 2, 7, 1, 4, 4 };
	vector<int> cost { 2, 4, 3, 5, 2, 1, 4, 5, 6, 6 };

	int start = can_complete_circuit(gas, cost); 
	cout << "Test case 1 returns "
	     << (start == -1 ? "True" : "False")
	     << endl;

	vector<int> cost2 { 2, 4, 3, 5, 2, 1, 4, 5, 1, 6 };
	start = can_complete_circuit(gas, cost2);
	cout << "Test case 2 returns "
	     << (start == 4 ? "True" : "False")
	     << endl;


	return 0;
}


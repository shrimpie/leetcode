// Problem description:
// 

// Idea:
// 1. 
// 2. 



#include <iostream>
#include <vector>

using namespace std;


void solve(vector<int>& A, int next, int last_i, int diff, int& cnt, 
	       vector<int>& sol)
{
    if(sol.size() >= 3)
    {
    	++cnt;
    	for(auto s : sol)
    		cout << s << ' ';
    	cout  << endl;
    }
    
    if(next < A.size())
    {
    	if(A[next] - A[last_i] == diff)
        {
        	sol.push_back(A[next]);
        	solve(A, next + 1, next, diff, cnt, sol);
    	}
    	else
    		solve(A, next + 1, last_i, diff, cnt, sol);
    }

}


int numberOfArithmeticSlices(vector<int>& A) {
    
    int n = A.size();
    
    if(n <= 2)
        return 0;
    
    int cnt = 0;
    vector<int> sol;
    // vector<vector<int> > res;
    
    for(int start = 0; start <= n - 3; ++start)
    {
        for(int next = start + 1; next <= n - 2; ++next)
        {
        	sol.push_back(A[start]);
            sol.push_back(A[next]);
            solve(A, next + 1, next, A[next] - A[start], cnt, sol);
            sol.clear();
        }
        sol.clear();
    }
    
    return cnt;
}





int main()
{

	// vector<int> nums = { 2, 4, 6, 8, 10 };
	vector<int> nums = { 7, 7, 7, 7 };
	int ans = numberOfArithmeticSlices(nums);

	cout << "ans: " << ans << endl;
	// cout << "Test case returns "
	//      << (   ? "True" : "False")
	//      << endl;




	return 0;
}


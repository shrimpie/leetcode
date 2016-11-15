// Problem description:
// Shuffle a set of numbers without duplicates.


// Idea: reservoir sampling
// 1. First time pick a random number and save it.
// 2. Next time pick a number from remaining set, and save it.
// 3. Go on until the last item is met.



#include <iostream>
#include <vector>

using namespace std;


vector<int> shuffle(vector<int>& v)
{
	vector<int> res = v;
	int size = v.size();
	for(int i = 0; i < size; ++i)
	{
		int idx = rand() % (size - i);
		swap(res[i], res[idx+i]);
	}
	return res;
}

vector<vector<int> > perm(vector<int>& num)
{
	vector<vector<int> > all_pers;

	if(num.empty())
		return all_pers;
	// Insert the first element to start.
	all_pers.push_back(vector<int>(1, num[0]));
	for(int i = 1; i < num.size(); ++i)
	{
		int n = all_pers.size();
		for(int j = 0; j < n; ++j)
		{
			// For each of permutations currently got,
			// Insert next number 
			for(int k = 0; k < all_pers[j].size(); ++k)
			{
				vector<int> per = all_pers[j];
				per.insert(per.begin() + k, num[i]);
				all_pers.push_back(per);
			}
			// Don't forget the last position of jth.
			all_pers[j].push_back(num[i]);
		}
	}

	return all_pers;
}

bool validate_shuffle(vector<int>& v, vector<int> f(vector<int>&), int trials, 
	                  double error_rate)
{
	auto perms = perm(v);
	int size = perms.size();
	vector<int> cnt(size, 0);

	for(int i = 0; i < size * trials; ++i)
	{
		auto res = f(v);
		for(int i = 0; i < size; ++i)
		{
			if(res == perms[i])
			{
				++cnt[i];
				break;
			}
		}
	}

	// for(auto c : cnt)
	// 	cout << c << ", ";
	// cout << endl;

	int error = (int)(trials * error_rate);
	for(int i = 0; i < size; ++i)
	{
		if(abs((cnt[i] - trials)) > error)
			return false;
	}

	return true;
}


int main()
{

	vector<int> v { 1, 2, 3 };

	srand(time(NULL));

	// auto ans = shuffle(v);
	int trials = 100000;
	double max_error_rate = 0.01;

	cout << "Test case 1 returns "
	     << (validate_shuffle(v, shuffle, trials, max_error_rate) 
	     	 ? "True" : "False")
	     << endl;


	return 0;
}


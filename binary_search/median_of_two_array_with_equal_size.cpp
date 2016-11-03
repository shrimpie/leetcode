#include <iostream>
#include <vector>

using namespace std;

// arr: the vector to find median within
// start: first index to consider in the vector
// size: valid number of items to consider
double median(vector<int>& arr, int start, int size)
{
	if(size % 2 == 0)
		return (arr[start + size/2] + arr[start + size/2 -1]) / 2.0;
	return (double)(arr[start + size/2]);
}

// arr1: first vector
// start1: first index of first vector
// arr2: second vector
// start2: first index of second vector
// size: size of both vectors to consider
double get_median(vector<int>& arr1, int start1, 
                  vector<int>& arr2, int start2,
                  int size)
{
	if(size <= 0)
		return -1;
	if(size == 1)
		return (arr1[start1] + arr2[start2]) / 2.0;
	if(size == 2)
		return (max(arr1[start1], arr2[start2]) + 
			    min(arr1[start1+1], arr2[start2+1])) / 2.0;

	double m1 = median(arr1, start1, size);
	double m2 = median(arr2, start2, size);

	if(m1 == m2)
		return m1;

	// If m1 < m2 then median must exist in arr1[m1...] and arr2[...m2]
	if(m1 < m2)
	{
		if(size % 2 == 0)
			return get_median(arr1, start1 + size/2 - 1,
				              arr2, start2,
				              size - size/2 + 1);
		return get_median(arr1, start1 + size/2,
                          arr2, start2,
                          size - size/2);
	}

	// If m1 > m2 then median must exist in arr1[...m1] and arr2[m2...]
	if(size % 2 == 0)
		return get_median(arr2, start2 + size/2 - 1,
				          arr1, start1,
				          size - size/2 + 1);
	return get_median(arr2, start2 + size/2,
                      arr1, start1,
                      size - size/2);
}


int main()
{
	vector<int> a { 1, 2, 3, 4 };
	vector<int> b { 2, 4, 6, 8 };

	cout << "Normal test case returns: " 
	     << (3.5 == get_median(a, 0, b, 0, a.size()) ? "True" : "False")
	     << endl;

	vector<int> c { 1 };
	vector<int> d { 2 };

	cout << "Vectors with one item test case returns: " 
	     << (1.5 == get_median(c, 0, d, 0, c.size()) ? "True" : "False")
	     << endl;

	vector<int> e { };
	vector<int> f { };

	cout << "Empty vector test case returns: " 
	     << (-1 == get_median(e, 0, f, 0, e.size()) ? "True" : "False")
	     << endl;

	vector<int> g;
	vector<int> h;

	for(int i = 0; i < 1000; ++i)
	{
		g.push_back(2*i);
		h.push_back(2*i + 1);
	}

	cout << "Long vector test case returns: " 
	     << (999.5 == get_median(g, 0, h, 0, g.size()) ? "True" : "False")
	     << endl;

	return 0;
}


















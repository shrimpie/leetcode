// Implement pow(x, n).

#include <iostream>

using namespace std;


double my_power(double x, int n)
{
	if(n == 0)
		return 1;
	if(n == 1)
		return x;
	if(n == 2)
		return x * x;
	double half = my_power(x, n/2);
	if(n % 2)
		return half * half * x;
	else
		return half * half;
}

// x: the number to be raised
// n: the times x gonna be raised to.
double my_pow(double x, int n)
{
	if(x > 1 && n == INT_MIN)
		return 0.0;
	if(n < 0)
		return 1 / my_power(x, -n);
	return my_power(x, n);
}




int main()
{

	double d = 8.88023;
	cout << "Test case 1 returns: "
	     << (((my_pow(d, 3) - 700.28148) <= 1e-5) ? "True" : "False")
	     << endl;

	d = 10000.0;
	cout << "Test case 2 returns: "
	     << (((my_pow(d, 3) == 1e12) ? "True" : "False"))
	     << endl;



	return 0;
}
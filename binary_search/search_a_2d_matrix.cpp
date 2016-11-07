// Problem description:
// Write an efficient algorithm that searches for a value in an mxn matrix. 
// This matrix has the following properties:
//  * Integers in each row are sorted from left to right.
//  * The first integer of each row is greater than the last integer of the
//    previous row.
// For example:
// Considering the following matrix:
// [
//   [1, 3, 5, 7],
//   [10, 11, 16, 20],
//   [23, 30, 34, 50]
// ]
// Given target = 3, return true.

// Idea:
// 1. Locate which row the target might be in.
// 2. Normal binary search for the target.



#include <iostream>
#include <vector>

using namespace std;


bool search_matrix(vector<vector<int>>& matrix, int target) {
    int row = matrix.size();
    if(row == 0)
        return false;
    int col = matrix[0].size();
    int low = 0, high = row - 1;

    // Strictly less than, no equal
    while(low < high)
    {
        // Binary search to locate row.
        int mid = (low + high) / 2;
        // If the target less than the 1st item of row mid,
        // then it must be in rows before mid.
        if(target < matrix[mid][0])
            high = mid - 1;         
        // If target greater than 1st item of row mid,
        else if(target > matrix[mid][0])
        {
        	// need check if greater than last item of row mid.
            if(target > matrix[mid][col - 1]) // If > last item of row mid, 
                low = mid + 1;                // it must be in rows after mid.
            else
            {                                 // Otherwise, it's in row mid.
                low = mid;                    // And break.
                break;
            }
        }
        else return true;           // If == , you found it.
    }
    int k = low;                    // the data is in row `low`
    low = 0; 
    high = col - 1;                 // Normal binary search.
    while(low <= high)
    {
        // binary search in the row.
        int mid = (low + high) / 2;
        if(target < matrix[k][mid])
            high = mid - 1;
        else if(target > matrix[k][mid])
            low = mid + 1;
        else
            return true;  
    }
    return false;
}



int main()
{

	vector<vector<int> > matrix { {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
	int target = 3;
	cout << "Test case 1 returns "
	     << (search_matrix(matrix, target) == true ? "True" : "False")
	     << endl;

	return 0;
}


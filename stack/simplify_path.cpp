// Problem description:
// Given an absolute path for a file (Unix style), simplify it.
// For example,
//   path = "/home/", => "/home"
//   path = "/a/./b/../../c/", => "/c"

// Idea:
// 1. "/": directory separator,
// 2. ".": current directory,
// 3. "..": parent directory,
// 4. others: directory name.

// The key here is to find all dirs, and if met "..", delete previous dir.

// Corner cases:
// 1. path = "/../", return "/",
// 2. multiple slashes, ignore redundant slashes.

// Not exactly stack category, but pretty close.


#include <iostream>
#include <vector>

using namespace std;

string simplify_path(string path)
{
	string ret, curDir;
	vector<string> allDir;

	path.push_back('/');
	for(int i = 0; i < path.size(); ++i)
	{
	    if(path[i] == '/')
	    {
	        if(curDir.empty())          // If cur dir empty, just go on.
	            continue;
	        else if(curDir == ".")      // If cur dir is ".", it's redundant, clear it.
	            curDir.clear();
	        else if(curDir == "..")     // If cur dir is "..",
	        {
	            if(!allDir.empty())     // If res dir is not empty, remove the last one.
	                allDir.pop_back();
	            curDir.clear();         // Then clear cur dir as well.
	        }
	        else                        // Normal dir, add it.
	        {
	            allDir.push_back(curDir);
	            curDir.clear();         // Reset cur dir.
	        }
	    }
	    else
	        curDir.push_back(path[i]); // Keep adding for current dir.
	}

	for(int i = 0; i < allDir.size(); ++i) // Construct the final dir.
	    ret.append("/" + allDir[i]);

	if(ret.empty())                    // Corner case, if empty result, return "/"
	    ret = "/";

	return ret;
}



int main()
{
	vector<string> dirs { "/home/", "/a/./b/../../c/" };
	vector<string> tgt { "/home", "/c" };
	for(int i = 0; i < dirs.size(); ++i)
	{
		cout << "Test case " << i + 1 << " returns "
	         << (simplify_path(dirs[i]) == tgt[i] ? "True" : "False")
	         << endl;
	}
	




	return 0;
}


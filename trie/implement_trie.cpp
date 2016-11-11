// Problem description:
// Implement a trie with insert, search, and startsWith methods.

// Note:
// You may assume that all inputs consist of lower case letters a-z.



#include <iostream>
#include <vector>

using namespace std;


struct TrieNode {
	int val;
	TrieNode* children[26];
	TrieNode()
	{
		val = 0;
		for(int i = 0; i < 26; ++i)
			children[i] = NULL;
	}
};

class Trie {
private:
	TrieNode* root;
	int count;
public:
	Trie()
	{
		root = new TrieNode();
		count = 0;
	}

	void insert(string word)
	{
		TrieNode* p = root;
		int len = word.size();
		for(int i = 0; i < len; ++i)
		{
			int index = word[i] - 'a';
			if(!p->children[index])
				p->children[index] = new TrieNode();
			p = p->children[index];
		}
		++count;
		p->val = count;
	}

	bool search(string word)
	{
		TrieNode* p = root;
		int len = word.size();
		for(int i = 0; i < len; ++i)
		{
			int index = word[i] - 'a';
			if(p->children[index])
				p = p->children[index];
			else
				return false;
		}
		if(p->val)
			return true;
		return false;
	}

	bool startsWith(string word)
	{
		TrieNode* p = root;
		int len = word.size();
		for(int i = 0; i < len; ++i)
		{
			int index = word[i] - 'a';
			if(p->children[index])
				p = p->children[index];
			else
				return false;
		}

		return true;
	}
};



int main()
{
	Trie trie;

	trie.insert("something");

	cout << "Test case 1 returns "
	     << (trie.search("key") == false ? "True" : "False")
	     << endl;

	cout << "Test case 2 returns "
	     << (trie.search("something") == true ? "True" : "False")
	     << endl;

	cout << "Test case 3 returns "
	     << (trie.startsWith("some") == true ? "True" : "False")
	     << endl;


	return 0;
}


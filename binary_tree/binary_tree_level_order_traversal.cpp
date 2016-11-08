// Problem description:
// Given a binary tree, return the level order traversal of its nodes' values.
// (ie, from left to right, level by level).
// 

// Idea:
// 1. The key is to distinguish which level you are currently on.
// 2. Two methods:
//    a) use two containers to store current level and next level.
//    b) use a queue, but have to store additional level info.
//    c) well, you could also push a NULL node, but for not balanced binary tree,
//       this will add O(n) of push and pop of NULL node.




#include <iostream>
#include <vector>
#include <queue>
#include <stack>


using namespace std;


struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct LevelNode
{
	TreeNode* node;
	int level;
	LevelNode(TreeNode* n, int l) : node(n), level(l) {}
};


class BinaryTree
{
private:
	TreeNode* root;

	void add_node(int v, TreeNode* n)
	{
		if(v <= n->val)
		{
			if(n->left)
				add_node(v, n->left);
			else
				n->left = new TreeNode(v);
		}
		else
		{
			if(n->right)
				add_node(v, n->right);
			else
				n->right = new TreeNode(v);
		}
	}

public:

	BinaryTree() : root(NULL) {}

	TreeNode* get_root()
	{
		return root;
	}

	void add_node(int v)
	{
		if(!root)
			root = new TreeNode(v);
		else
			add_node(v, root);
	}

	// This one uses two containers.
	vector<vector<int> > level_order_traverse()
	{
		vector<vector<int> > level_node_values;
		if(!root)
			return level_node_values;

		vector<TreeNode*>* cur_level = new vector<TreeNode*>();
		vector<TreeNode*>* next_level = new vector<TreeNode*>();
		cur_level->push_back(root);

		while(!cur_level->empty())
		{
			// scan current level, collect values of cur_level nodes, and 
			// genenrate next level's.
			vector<int> cur_level_values;
			for(int i = 0; i < cur_level->size(); ++i)
			{
				TreeNode* cur_node = (*cur_level)[i];
				cur_level_values.push_back(cur_node->val);
				if(cur_node->left)
					next_level->push_back(cur_node->left);
				if(cur_node->right)
					next_level->push_back(cur_node->right);
			}
			level_node_values.push_back(cur_level_values);
			// Swap cur_level and next_level, and clear next_level
			vector<TreeNode*>* tmp = cur_level;
			cur_level = next_level;
			next_level = tmp;
			next_level->clear();
		}

		return level_node_values;
	}

	// This one uses a queue.
	vector<vector<int> > level_order_traverse2()
	{
		vector<vector<int> > level_node_values;
		if(!root)
			return level_node_values;

		queue<LevelNode> q;
		// Level 0 to start.
		q.push(LevelNode(root, 0));

		while(!q.empty())
		{
			LevelNode cur_level_node = q.front();
			TreeNode* cur_node = cur_level_node.node;
			int cur_level = cur_level_node.level;
			q.pop();

			if(cur_level == level_node_values.size())
				level_node_values.push_back(vector<int>(0, 0));
			level_node_values[cur_level].push_back(cur_node->val);

			if(cur_node->left)
				q.push(LevelNode(cur_node->left, cur_level + 1));
			if(cur_node->right)
				q.push(LevelNode(cur_node->right, cur_level + 1));
			
		}

		return level_node_values;
	}


	// This one uses a queue and a NULL marker.
	vector<vector<int> > level_order_traverse3()
	{
		vector<vector<int> > res;
		if(!root)
			return res;

		queue<TreeNode*> q;
		q.push(root);
		q.push(NULL);

		int cur_level = 0;

		while(!q.empty())
		{
			auto cur_node = q.front();
			q.pop();

			if(!cur_node)
			{
				++cur_level;
				if(!q.empty())
					q.push(NULL);
				continue;
			}
			if(cur_level == res.size())
				res.push_back(vector<int>(0, 0));
			res[cur_level].push_back(cur_node->val);

			if(cur_node->left)
				q.push(cur_node->left);
			if(cur_node->right)
				q.push(cur_node->right);
		}

		return res;
	}

	// This one traverse in a zigzag manner.
	vector<vector<int> > zigzag_level_traverse()
	{
		vector<vector<int> > res;
		if(!root)
			return res;

		stack<TreeNode*>* cur_level = new stack<TreeNode*>();
		stack<TreeNode*>* next_level = new stack<TreeNode*>();		

		cur_level->push(root);
		bool left2right = true;

		while(!cur_level->empty())
		{
			vector<int> cur_level_val;
			while(!cur_level->empty())
			{
				TreeNode* cur = cur_level->top();
				cur_level->pop();
				cur_level_val.push_back(cur->val);

				if(left2right)
				{
					if(cur->left)
						next_level->push(cur->left);
					if(cur->right)
						next_level->push(cur->right);
				}
				else
				{
					if(cur->right)
						next_level->push(cur->right);
					if(cur->left)
						next_level->push(cur->left);
				}
			}
			res.push_back(cur_level_val);
			// swap
			auto tmp = cur_level;
			cur_level = next_level;
			next_level = tmp;

			left2right = !left2right;
		}

		return res;
	}

	~BinaryTree()
	{
		free_node(root);
	}

	void free_node(TreeNode* leaf)
	{
		if(leaf)
		{
			free_node(leaf->left);
			free_node(leaf->right);
			delete leaf;
		}
	}

};


int main()
{

	BinaryTree t;
	vector<int> nums { 5, 2, 7, 1, 4, 8, 9, 3 };
	for(int i = 0; i < nums.size(); ++i)
		t.add_node(nums[i]);

	auto ans = t.level_order_traverse();
	vector<vector<int> > tgt { { 5 }, { 2, 7 }, { 1, 4, 8 }, { 3, 9 } };

	bool res = true;
	for(int i = 0; i < ans.size(); ++i)
	{
		res &= (ans[i].size() == tgt[i].size());
		for(int j = 0; j < ans[i].size(); ++j)
			res &= (ans[i][j] == tgt[i][j]);
	}
	cout << "Test case 1 returns "
	     << (res == true ? "True" : "False")
	     << endl;

	ans = t.level_order_traverse2();
	res = true;
	for(int i = 0; i < ans.size(); ++i)
	{
		res &= (ans[i].size() == tgt[i].size());
		for(int j = 0; j < ans[i].size(); ++j)
			res &= (ans[i][j] == tgt[i][j]);
	}
	cout << "Test case 2 returns "
	     << (res == true ? "True" : "False")
	     << endl;

	ans = t.level_order_traverse3();
	res = true;
	for(int i = 0; i < ans.size(); ++i)
	{
		res &= (ans[i].size() == tgt[i].size());
		for(int j = 0; j < ans[i].size(); ++j)
			res &= (ans[i][j] == tgt[i][j]);
	}
	cout << "Test case 3 returns "
	     << (res == true ? "True" : "False")
	     << endl;


	ans = t.zigzag_level_traverse();
	vector<vector<int> > tgt2 { { 5 }, { 7, 2 }, { 1, 4, 8 }, { 9, 3 } };

	res = true;
	for(int i = 0; i < ans.size(); ++i)
	{
		res &= (ans[i].size() == tgt2[i].size());
		for(int j = 0; j < ans[i].size(); ++j)
			res &= (ans[i][j] == tgt2[i][j]);
	}
	cout << "Test case 4 returns "
	     << (res == true ? "True" : "False")
	     << endl;

	return 0;
}


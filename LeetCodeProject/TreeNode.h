#pragma once

#ifdef LIBRARY_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#include <vector>

using namespace std;

//struct DllExport TreeNode {
//	int val;
//	TreeNode* left;
//	TreeNode* right;
//	TreeNode() : val(0), left(nullptr), right(nullptr) {}
//	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};


class DllExport Node {

public:
	int val;
	vector<Node*> neighbors;

public:
	Node();
	Node(int _val);
	Node(int _val, vector<Node*> _neighbors);

	~Node();
};
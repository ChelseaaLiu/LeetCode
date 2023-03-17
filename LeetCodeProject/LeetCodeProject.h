#pragma once
#ifdef MATHLIBRARY_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#include <vector>
#include <string>

using namespace std;

// Definition for a binary tree node.
struct DllExport TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class DllExport PrintVector
{
public:
	void print_2d_vec(vector<vector<int>>& vec);

private:

};

class DllExport DP : public PrintVector
{
public : 

	vector<vector<int>> generate(int numRows);
	int lengthOfLIS(vector<int>& nums);//300
	int fib(int n); //509
	int tribonacci(int n); // 1137
};

class DllExport DFSBFS
{
public:

	int minDepth(TreeNode* root);

};

class DllExport Backtracking
{
public:

	vector<vector<int>> combinationSum(vector<int>& candidates, int target); // 39

private:

	void _helper(vector<vector<int>>& ans, vector<int>& subAns, const vector<int>& candidates,
		const int& target, const int& sum, const int& i);
};

class DllExport Solution : public DP, public DFSBFS, public Backtracking
{
public:

	Solution();

	bool isValid(string s); // 20. (string & stack)
	int removeDuplicates(vector<int>& nums); // 26. (array & two pointers)
	int smallestEvenMultiple(int n); // 2413
};


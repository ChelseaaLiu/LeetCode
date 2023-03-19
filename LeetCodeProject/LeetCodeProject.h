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

	template <class T>
	void print_1d_vec(vector<T>& vec);
private:

};

class DllExport DP : public PrintVector
{
public : 

	vector<vector<int>> generate(int numRows); // 118
	int lengthOfLIS(vector<int>& nums);//300
	int fib(int n); //509
	int tribonacci(int n); // 1137
};

class DllExport DFSBFS
{
public:

};

class DllExport Backtracking : public PrintVector
{
public:

	vector<vector<int>> combinationSum(vector<int>& candidates, int target); // 39

	vector<vector<int>> combinationSum2(vector<int>& candidates, int target); // 40
	vector<vector<int>> subsets(vector<int>& nums); // 78
	vector<vector<int>> subsetsWithDup(vector<int>& nums); // 90

	vector<vector<int>> permute(vector<int>& nums); // 46

private:

	void _helper(vector<vector<int>>& ans, vector<int> subAns, const vector<int>& candidates,
		const int& target, const int& sum, const int& i);

	void _helper2(vector<vector<int>>& ans, vector<int>& subAns,
		const vector<int>& candidates, const int& target, const int& sum, const int& i);

	void _helper3(vector<vector<int>>& ans, vector<int>& subAns, const vector<int>& candidates,
		const int& i, const bool& isRepeated);
};

class DllExport Solution4 : public PrintVector
{
public:
	vector<double> sampleStats(vector<int>& count);//1093
	int countBalls(int lowLimit, int highLimit); //1742
	string largestGoodInteger(string num); //2264


private:

	double _get_median(vector<int>& count, const int& num);
};


class DllExport Solution : public DP, public DFSBFS, 
	public Backtracking, public Solution4
{
public:

	Solution();

	bool isValid(string s); // 20. (string & stack)
	int removeDuplicates(vector<int>& nums); // 26. (array & two pointers)
	int smallestEvenMultiple(int n); // 2413


};


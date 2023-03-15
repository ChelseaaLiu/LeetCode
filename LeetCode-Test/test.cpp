#include "pch.h"
#include "../LeetCodeProject/LeetCodeProject.h"
#include <array>
using namespace std;

// template<class T, size_t SIZE>
class DPTests : public ::testing::Test {

protected:
	template<size_t SIZE>
	void generate_118(int numRows, const array<int, SIZE>& arr);

};

template<size_t SIZE>
void DPTests::generate_118(int numRows, const array<int, SIZE>& arr)
{

	Solution sol;
	vector<vector<int>> vec = sol.generate(numRows);
	// sol.print_2d_vec(vec);

	auto arrIdx = 0;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		for (size_t j = 0; j < vec[i].size(); ++j)
		{
			ASSERT_LT(arrIdx, arr.size());
			EXPECT_EQ(arr[arrIdx++], vec[i][j]);
			// cout << vec[i][j] << " ";
		}
	}
}

class OtherTests : public ::testing::Test {

protected:

};


TEST_F(DPTests, TestGenerate){

	array<int, 15> arr{ {1, 1, 1, 1, 2, 1, 1, 3, 3, 1, 1, 4, 6, 4, 1 } };
	for (size_t i = 0; i < 5; i++)
	{
		generate_118(i+1, arr);
	}
}
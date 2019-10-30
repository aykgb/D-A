/*
 * @lc app=leetcode id=78 lang=cpp
 *
 * [78] Subsets
 *
 * https://leetcode.com/problems/subsets/description/
 *
 * algorithms
 * Medium (55.91%)
 * Likes:    2477
 * Dislikes: 60
 * Total Accepted:    434.8K
 * Total Submissions: 777.8K
 * Testcase Example:  '[1,2,3]'
 *
 * Given a set of distinct integers, nums, return all possible subsets (the
 * power set).
 *
 * Note: The solution set must not contain duplicate subsets.
 *
 * Example:
 *
 *
 * Input: nums = [1,2,3]
 * Output:
 * [
 * ⁠ [3],
 * [1],
 * [2],
 * [1,2,3],
 * [1,3],
 * [2,3],
 * [1,2],
 * []
 * ]
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

#include "tools.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> subset;
    vector<vector<int>> result;
    dfs_subsets(nums, 0, subset, result);
    return result;
  }

  void dfs_subsets(vector<int>& nums, int start, vector<int>& subset, vector<vector<int>>& result) {
    result.emplace_back(subset);  // 把上一层的subset 放到result中
    for (int i = start; i < nums.size(); i++) { // 终止条件 —— 遍历到最后一个元素
      subset.emplace_back(nums[i]);             // 处理本层，本层可选的数加入set
      dfs_subsets(nums, i + 1, subset, result); // 向下递推一层
      subset.pop_back();                        // 回溯
    }
  }
};
// @lc code=end

int main() {
  vector<int> nums{1, 2, 3, 4, 5};

  Solution().subsets(nums);

  return 0;
}

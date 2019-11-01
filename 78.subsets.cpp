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
    // dfs_subsets(nums, 0, subset, result);
    // dfs_subsets2(nums, 0, subset, result);
    // dfs_subsets3(nums, 0, subset, result);
    result.emplace_back(subset);
    for(auto& num : nums) {
      int size = result.size();
      for(int i = 0; i < size; i++)  {
        subset = result[i];
        subset.emplace_back(num);
        result.emplace_back(subset);
      }
    }
    return result;
  }

  // DFS搜索，第0层选空集合，第1层可选所有的数字，第2层自能选第一层之后的数字，按这个规则来可展开为一棵树，
  // result是搜索路径的集合
  void dfs_subsets(vector<int>& nums, int start, vector<int>& subset,
                   vector<vector<int>>& result) {
    result.emplace_back(subset);  // 把上一层的subset 放到result中
    for (int i = start; i < nums.size();
         i++) {  // 终止条件 —— 遍历到最后一个元素
      subset.emplace_back(nums[i]);  // 处理本层，本层可选的数加入set
      dfs_subsets(nums, i + 1, subset, result);  // 向下递推一层
      subset.pop_back();                         // 回溯
    }
  }

  //  DFS 选或者不选nums中的元素
  void dfs_subsets2(vector<int>& nums, int index, vector<int>& subset,
                    vector<vector<int>>& result) {
    // terminator
    if (index == nums.size()) {
      result.emplace_back(subset);
      return;
    }

    // process
    dfs_subsets2(nums, index + 1, subset, result);  // not pick, drill down

    subset.emplace_back(nums[index]);  // pick nums[index], drill down
    dfs_subsets2(nums, index + 1, subset, result);

    // reverse state
    subset.pop_back();
  }

  //  DFS
  //  选或者不选nums中的元素，这里对subset使用复制的方法，保证每层的subset都是local的
  void dfs_subsets3(vector<int>& nums, int index, vector<int> subset,
                    vector<vector<int>>& result) {
    // terminator
    if (index == nums.size()) {
      result.emplace_back(subset);
      return;
    }

    // process
    dfs_subsets3(nums, index + 1, subset, result);  // not pick, drill down

    subset.emplace_back(nums[index]);  // pick nums[index], drill down
    dfs_subsets3(nums, index + 1, subset, result);
  }
};
// @lc code=end

#include "tools.hpp"

int main() {
  vector<int> nums{1, 2, 3, 4, 5};

  print_subsets(Solution().subsets(nums));

  return 0;
}

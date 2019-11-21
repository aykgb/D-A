/*
 * @lc app=leetcode id=62 lang=cpp
 *
 * [62] Unique Paths
 *
 * https://leetcode.com/problems/unique-paths/description/
 *
 * algorithms
 * Medium (49.79%)
 * Likes:    2083
 * Dislikes: 152
 * Total Accepted:    356.2K
 * Total Submissions: 711.7K
 * Testcase Example:  '3\n2'
 *
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in
 * the diagram below).
 *
 * The robot can only move either down or right at any point in time. The robot
 * is trying to reach the bottom-right corner of the grid (marked 'Finish' in
 * the diagram below).
 *
 * How many possible unique paths are there?
 *
 *
 * Above is a 7 x 3 grid. How many possible unique paths are there?
 *
 * Note: m and n will be at most 100.
 *
 * Example 1:
 *
 *
 * Input: m = 3, n = 2
 * Output: 3
 * Explanation:
 * From the top-left corner, there are a total of 3 ways to reach the
 * bottom-right corner:
 * 1. Right -> Right -> Down
 * 2. Right -> Down -> Right
 * 3. Down -> Right -> Right
 *
 *
 * Example 2:
 *
 *
 * Input: m = 7, n = 3
 * Output: 28
 *
 */

#include <iostream>
#include <vector>

#include "tools.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  // 动规-优化版
  // 按行扫描，用记下的上一行数据计算当前行值，并更新到记忆数组中，只需要记下一行数据即可。
  int uniquePaths(int m, int n) {
    vector<int> pre_rows(m, 1);
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        pre_rows[j] = pre_rows[j - 1] + pre_rows[j];
      }
    }

    return pre_rows[m - 1];
  }

  // 动规
  int uniquePaths3(int m, int n) {  // m 列 n 行
    vector<vector<int>> dp(n, vector<int>(m, 1));
#ifdef TOOLS
    print_subsets(dp);
#endif
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
#ifdef TOOLS
        print_subsets(dp);
#endif
      }
    }
    return dp[n - 1][m - 1];
  }

  // 递归 - 以始为终，反向递推
  int uniquePaths2(int m, int n) {
    if (m < 1 || n < 1) { // !越界
      return 0;
    }
    // if (m == 1 || n == 1) {
    if (m == 1 && n == 1) { // !抵达终点destination
      return 1;
    }
    return uniquePaths2(m - 1, n) + uniquePaths2(m, n - 1);
  }
};
// @lc code=end

int main() {
  std::cout << Solution().uniquePaths3(9, 9) << std::endl;
  std::cout << Solution().uniquePaths2(9, 9) << std::endl;

  return 0;
}

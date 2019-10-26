/*
 * @lc app=leetcode id=22 lang=cpp
 *
 * [22] Generate Parentheses
 *
 * https://leetcode.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (57.72%)
 * Likes:    3475
 * Dislikes: 206
 * Total Accepted:    411.4K
 * Total Submissions: 712.7K
 * Testcase Example:  '3'
 *
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 *
 *
 * For example, given n = 3, a solution set is:
 *
 *
 * [
 * ⁠ "((()))",
 * ⁠ "(()())",
 * ⁠ "(())()",
 * ⁠ "()(())",
 * ⁠ "()()()"
 * ]
 *
 */

#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  // 递归解法 - 递归函数，中open close 初始化为n，表示可以添加的左右括号数量
  // 递归解法 - n对括号，展开成地归树，树高为2 * n，左括号总是大于等于右括号数量，最终左右括号个数相等，等于n
  vector<string> generateParenthesis(int n) {
    vector<string> result;
    generator("", 0, 0, n, result);
    return result;
  }

  // last 上一层的递推的结果, open 左括号个数, close 右括号个数, n对括号, result
  // 最终结果
  void generator(string last, int open, int close, int n,
                 vector<string>& result) {
    // terminator - 终止条件
    if (close == n) {
      result.push_back(last);
      return;
    }
    // process + drill down
    // 对上一层递推的结果，要么添加左括号，要么添加右括号
    if (open < n) {
      // 左括号小于n，可以添加左括号
      generator(last + "(", open + 1, close, n, result);
    }
    if (close < open) {
      // 右括号小于左括号，可以添加右括号
      generator(last + ")", open, close + 1, n, result);
    }
    // reverse state
  }
};
// @lc code=end

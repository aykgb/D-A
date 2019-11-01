/*
 * @lc app=leetcode id=50 lang=cpp
 *
 * [50] Pow(x, n)
 *
 * https://leetcode.com/problems/powx-n/description/
 *
 * algorithms
 * Medium (28.72%)
 * Likes:    1011
 * Dislikes: 2431
 * Total Accepted:    373.2K
 * Total Submissions: 1.3M
 * Testcase Example:  '2.00000\n10'
 *
 * Implement pow(x, n), which calculates x raised to the power n (x^n).
 *
 * Example 1:
 *
 *
 * Input: 2.00000, 10
 * Output: 1024.00000
 *
 *
 * Example 2:
 *
 *
 * Input: 2.10000, 3
 * Output: 9.26100
 *
 *
 * Example 3:
 *
 *
 * Input: 2.00000, -2
 * Output: 0.25000
 * Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25
 *
 *
 * Note:
 *
 *
 * -100.0 < x < 100.0
 * n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]
 *
 *
 */
#include <iostream>

using namespace std;

// @lc code=start
class Solution {
 public:
  // 1. 暴力法
  // 2. 分治法，使用递归，
  //    模板: 1).terminator
  //         2).process
  //         3).drill down, merge result
  //         4).reverse state

  double myPow2(double x, int64_t n) {
    if(n == 0) {
      return 1.0;
    }
    if(n == 1) {
      return x;
    }
    if(n < 0) {
      return 1.0 / myPow(x, -n);
    }

    double res = 0.0;
    if(n % 2 == 1) {
      res = myPow2(x, n/2 + 1) * myPow(x, n/2);
    } else {
      res = myPow2(x, n/2);
      res *= res;
    }

    return res;
  }

  double myPow(double x, int n) {
    if (n == 0) {
      return 1.0;
    }
    return fastPow(x, n);
  }

  double fastPow(double x, int n) {
    if (n < 0) return 1.0 / fastPow(x, -n);
    double res = 1.0;
    for (int i = n; i != 0; i = i / 2) {
      if (i % 2 != 0) {
        res = res * x;
      }
      x *= x;
    }
    return res;
  }
};
// @lc code=end

int main() {
  Solution().myPow(2, 5);
  return 0;
}

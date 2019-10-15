/*
 * @lc app=leetcode id=70 lang=cpp
 *
 * [70] Climbing Stairs
 *
 * https://leetcode.com/problems/climbing-stairs/description/
 *
 * algorithms
 * Easy (45.25%)
 * Likes:    2754
 * Dislikes: 97
 * Total Accepted:    489K
 * Total Submissions: 1.1M
 * Testcase Example:  '2'
 *
 * You are climbing a stair case. It takes n steps to reach to the top.
 *
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can
 * you climb to the top?
 *
 * Note: Given n will be a positive integer.
 *
 * Example 1:
 *
 *
 * Input: 2
 * Output: 2
 * Explanation: There are two ways to climb to the top.
 * 1. 1 step + 1 step
 * 2. 2 steps
 *
 *
 * Example 2:
 *
 *
 * Input: 3
 * Output: 3
 * Explanation: There are three ways to climb to the top.
 * 1. 1 step + 1 step + 1 step
 * 2. 1 step + 2 steps
 * 3. 2 steps + 1 step
 *
 *
 */

#include <assert.h>
#include <iostream>

using namespace std;

// @lc code=start
class Solution {
 public:
  // 每次只能走1步或2步，对于第N阶楼梯，可以走1步或走2步到达N，所以有递推式
  // f(N) = f(N-1) + f(N -2)
  // 斐波那锲数列
  // 纯递归方法求第N项的值
  int fibonacci(int n) {
    if (n <= 2) {
      return 1;
    }
    return fibonacci(n - 2) + fibonacci(n - 1);
  }

  // 尾调用：函数返回值当做当前函数的返回值；
  // 尾递归：函数调用的是
  int fibonacci_tail(int n, int a, int b) {
    if (n <= 2) {
      return b;
    }
    return fibonacci_tail(n - 1, b, a + b);
  }

  int fibonacci_loop(int n) {
    if (n <= 2) {
      return 1;
    }
    int a = 1, b = 1, c = a + b;
    for (int i = 0; i < n - 2; i++) {
      c = a + b;
      a = b;
      b = c;
    }
    return c;
  }

  int fibonacci_loop2(int n) {
    if (n <= 2) {
      return 1;
    }
    int f[3];
    f[0] = 1, f[1] = 1, f[2] = 0;
    for (int i = 0; i < n - 2; i++) {
      f[2] = f[0] + f[1];
      f[0] = f[1];
      f[1] = f[2];
    }
    return f[2];
  }

  int climbStairs(int n) { return fibonacci_loop(n + 1); }
  // !求阶梯数为n的攀登方法，是斐波那锲数列的第n+1项
};
// @lc code=end

int main() {
  for (int n = 1; n < 10; n++) {
    std::cout << "n " << n << " | " << Solution().climbStairs(n) << std::endl;
  }
}

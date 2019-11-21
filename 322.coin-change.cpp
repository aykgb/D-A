/*
 * @lc app=leetcode id=322 lang=cpp
 *
 * [322] Coin Change
 *
 * https://leetcode.com/problems/coin-change/description/
 *
 * algorithms
 * Medium (32.29%)
 * Likes:    2458
 * Dislikes: 88
 * Total Accepted:    268.5K
 * Total Submissions: 827.6K
 * Testcase Example:  '[1,2,5]\n11'
 *
 * You are given coins of different denominations and a total amount of money
 * amount. Write a function to compute the fewest number of coins that you need
 * to make up that amount. If that amount of money cannot be made up by any
 * combination of the coins, return -1.
 *
 * Example 1:
 *
 *
 * Input: coins = [1, 2, 5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1
 *
 * Example 2:
 *
 *
 * Input: coins = [2], amount = 3
 * Output: -1
 *
 *
 * Note:
 * You may assume that you have an infinite number of each kind of coin.
 *
 */

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    // 1. terminator
    if (amount == 0) {
      return 0;
    }
    int ans = std::numeric_limits<int>::max();
    // 2. process current level
    for (auto& coin : coins) {
      int remain = amount - coin;
      if (remain < 0) continue;
      // 3. drill down
      int subAns = coinChange(coins, remain);
      if (subAns == -1) continue;
      ans = std::min(ans, subAns + 1);
    }

    return ans == std::numeric_limits<int>::max() ? -1 : ans;
    // 4. reverse state if necessary
  }
};
// @lc code=end

int main() {
  {
    vector<int> coins{1, 2, 5};
    std::cout << Solution().coinChange(coins, 11) << std::endl;
  }

  {
    vector<int> coins{2};
    std::cout << Solution().coinChange(coins, 3) << std::endl;
  }
  return 0;
}

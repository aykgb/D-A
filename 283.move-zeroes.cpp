/*
 * @lc app=leetcode id=283 lang=cpp
 *
 * [283] Move Zeroes
 */

#include <iostream>
#include <vector>

#include "tools.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  void moveZeroes2(vector<int>& nums) {
    int lastNonZero = -1;  // 指向非0元素最后一个位置
    for (size_t i = 0; i < nums.size(); i++) {
      /* code */
      if (nums[i] != 0) {
        lastNonZero++;
        if (lastNonZero != i) {
          std::swap(nums[i], nums[lastNonZero]);
        }
      }
    }
  }

  void moveZeroes(vector<int>& nums) {
    int count = 0;  // 非0元素个数
    for (size_t i = 0; i < nums.size(); i++) {
      /* code */
      if (nums[i] != 0) {
        nums[count++] = nums[i];
      }
    }
    while (count < nums.size()) {
      nums[count++] = 0;
    }
  }
};
// @lc code=end

int main() {
  vector<int> nums = {0, 1, 0, 3, 12};
  Solution().moveZeroes(nums);
}

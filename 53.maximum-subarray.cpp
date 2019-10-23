/*
 * @lc app=leetcode id=53 lang=cpp
 *
 * [53] Maximum Subarray
 *
 * https://leetcode.com/problems/maximum-subarray/description/
 *
 * algorithms
 * Easy (44.83%)
 * Likes:    5326
 * Dislikes: 216
 * Total Accepted:    664K
 * Total Submissions: 1.5M
 * Testcase Example:  '[-2,1,-3,4,-1,2,1,-5,4]'
 *
 * Given an integer array nums, find the contiguous subarray (containing at
 * least one number) which has the largest sum and return its sum.
 *
 * Example:
 *
 *
 * Input: [-2,1,-3,4,-1,2,1,-5,4],
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 *
 *
 * Follow up:
 *
 * If you have figured out the O(n) solution, try coding another solution using
 * the divide and conquer approach, which is more subtle.
 *
 */

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  // 本质是动规
  int maxSubArray(vector<int>& nums) {
    int max_sum = std::numeric_limits<int>::min();
    int sum = 0;
    for (auto& num : nums) {
      sum += num;
      if (sum > max_sum) {
        max_sum = sum;
      }
      if (sum < 0) {
        sum = 0;
      }
    }
    return max_sum;
  }

  int maxSubArray3(vector<int>& nums) {
    int result = std::numeric_limits<int>::min();
    int sumAtLast = -1;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      if (sumAtLast < 0) {
        sumAtLast = nums[i];
      } else {
        sumAtLast += nums[i];
      }

      if (sumAtLast > result) {
        result = sumAtLast;
      }
    }

    return result;
  }

  int maxSubArray2(vector<int>& nums) {
    int max_sum = std::numeric_limits<int>::min();
    for (int i = 0; i < nums.size(); i++) {
      int sum = 0;
      for (int j = i; j < nums.size(); j++) {
        sum += nums[j];
        if (sum > max_sum) {
          max_sum = sum;
        }
      }
    }
    return max_sum;
  }
};
// @lc code=end

int main() {
  vector<int> nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
  Solution().maxSubArray(nums);

  return 0;
}

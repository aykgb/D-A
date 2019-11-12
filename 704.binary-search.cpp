/*
 * @lc app=leetcode id=704 lang=cpp
 *
 * [704] Binary Search
 *
 * https://leetcode.com/problems/binary-search/description/
 *
 * algorithms
 * Easy (49.69%)
 * Likes:    353
 * Dislikes: 35
 * Total Accepted:    78.9K
 * Total Submissions: 158.7K
 * Testcase Example:  '[-1,0,3,5,9,12]\n9'
 *
 * Given a sorted (in ascending order) integer array nums of n elements and a
 * target value, write a function to search target in nums. If target exists,
 * then return its index, otherwise return -1.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [-1,0,3,5,9,12], target = 9
 * Output: 4
 * Explanation: 9 exists in nums and its index is 4
 *
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [-1,0,3,5,9,12], target = 2
 * Output: -1
 * Explanation: 2 does not exist in nums so return -1
 *
 *
 *
 *
 * Note:
 *
 *
 * You may assume that all elements in nums are unique.
 * n will be in the range [1, 10000].
 * The value of each element in nums will be in the range [-9999, 9999].
 *
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    if (target < nums[0] && target > nums[nums.size() - 1]) {
      return -1;
    }

    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) { // !left 和 right相交结束
      // int mid = left + (right - left) / 2;
      int mid = (right + left) / 2;
      if (target > nums[mid]) {
        left = mid + 1;
      } else if (target == nums[mid]) {
        return mid;
      } else {
        right = mid - 1;
      }
    }
    return -1;
  }
};
// @lc code=end

int main() {
  vector<int> nums{-1, 0, 3, 5, 9, 12};
  std::cout << Solution().search(nums, 3) << std::endl;
}

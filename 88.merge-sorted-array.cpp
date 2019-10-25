/*
 * @lc app=leetcode id=88 lang=cpp
 *
 * [88] Merge Sorted Array
 *
 * https://leetcode.com/problems/merge-sorted-array/description/
 *
 * algorithms
 * Easy (37.13%)
 * Likes:    1364
 * Dislikes: 3183
 * Total Accepted:    435.8K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,2,3,0,0,0]\n3\n[2,5,6]\n3'
 *
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as
 * one sorted array.
 *
 * Note:
 *
 *
 * The number of elements initialized in nums1 and nums2 are m and n
 * respectively.
 * You may assume that nums1 has enough space (size that is greater or equal to
 * m + n) to hold additional elements from nums2.
 *
 *
 * Example:
 *
 *
 * Input:
 * nums1 = [1,2,3,0,0,0], m = 3
 * nums2 = [2,5,6],       n = 3
 *
 * Output: [1,2,2,3,5,6]
 *
 */

#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  // 倒序排，不需要使用额外空间
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i > -1 && j > -1) {
      nums1[k--] = (nums1[i] > nums2[j] ? nums1[i--] : nums2[j--]);
    }
    while (i > -1) {
      nums1[k--] = nums1[i--];
    }
    while (j > -1) {
      nums1[k--] = nums2[j--];
    }
  }

  // 使用额外的辅助数组做合并，再交换到nums1
  void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> nums3(nums1.size());
    int i = 0, j = 0, k = 0;
    while (i < m && j < n) {
      if (nums1[i] < nums2[j]) {
        nums3[k++] = nums1[i++];
      } else {
        nums3[k++] = nums2[j++];
      }
    }
    while (i < m) {
      nums3[k++] = nums1[i++];
    }
    while (j < n) {
      nums3[k++] = nums2[j++];
    }
    nums1.swap(nums3);
  }
};
// @lc code=end

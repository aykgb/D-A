/*
 * @lc app=leetcode id=84 lang=cpp
 *
 * [84] Largest Rectangle in Histogram
 *
 * https://leetcode.com/problems/largest-rectangle-in-histogram/description/
 *
 * algorithms
 * Hard (32.47%)
 * Likes:    2407
 * Dislikes: 62
 * Total Accepted:    201.2K
 * Total Submissions: 619.7K
 * Testcase Example:  '[2,1,5,6,2,3]'
 *
 * Given n non-negative integers representing the histogram's bar height where
 * the width of each bar is 1, find the area of largest rectangle in the
 * histogram.
 *
 *
 *
 *
 * Above is a histogram where width of each bar is 1, given height =
 * [2,1,5,6,2,3].
 *
 *
 *
 *
 * The largest rectangle is shown in the shaded area, which has area = 10
 * unit.
 *
 *
 *
 * Example:
 *
 *
 * Input: [2,1,5,6,2,3]
 * Output: 10
 *
 *
 */

#include <iostream>
#include <stack>
#include <vector>

#include "tools.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  /**
   * 1. 暴力求解，枚举各种可能，对每种可能求maxArea，枚举时间复杂度是O(n^3)，
   *    找到最小的高度O(N)，最后是O(N^3)
   * 1. 暴力求解，对每个下标对应的高度作为计算高度，左右方向扩展，
   *    找到不小于当前高度的边界，计算面积，时间复杂度O(n^2)
   * 2. 使用栈，初始化栈底是-1，记录单调递增的下标，遇到小于栈顶值对应的高度，
   *    说明找到栈顶中记录的下标是右边界，开始，计算面积。
   *
   */
  int largestRectangleArea(vector<int>& heights) {
    int max_area = 0;
    vector<int> indexs;
    heights.push_back(0);
    for(int i  = 0; i< heights.size(); i++) {
      while(indexs.size() > 0 && heights[i] <= heights[indexs.back()]) {
        int height = heights[indexs.back()];
        indexs.pop_back();

        int left_boundary = indexs.size() > 0 ? indexs.back() : -1;
        max_area = std::max(max_area, height * (i - left_boundary - 1));
      }
      indexs.push_back(i);
    }

    return max_area;
  }

  int largestRectangleArea2(vector<int>& heights) {
    int max_area = 0;
    for (int i = 0; i < heights.size(); i++) {
      int left_boundary = i - 1, right_boundary = i + 1;
      while (left_boundary >= 0 && heights[left_boundary] >= heights[i])
        left_boundary--;
      while (right_boundary < heights.size() &&
             heights[right_boundary] >= heights[i])
        right_boundary++;
      max_area =
          std::max(max_area, (right_boundary - left_boundary - 1) * heights[i]);
    }
    return max_area;
  }

  int largestRectangleArea1(vector<int>& heights) {
    int max_area = 0;
    for (int i = 0; i < heights.size(); i++) {
      for (int j = i; j < heights.size(); j++) {
        int min_height = -1;
        for (int k = i; k <= j; k++) {
          min_height = std::min(min_height, heights[k]);
        }
        max_area = std::max(max_area, (j - i + 1) * min_height);
      }
    }
    return max_area;
  }
};
// @lc code=end

int main() {
  vector<int> nums = {2, 1, 2};
  std::cout << Solution().largestRectangleArea(nums) << "\n";
  return 0;
}

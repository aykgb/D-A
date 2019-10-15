/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 *
 * https://leetcode.com/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (47.07%)
 * Likes:    4078
 * Dislikes: 479
 * Total Accepted:    465.1K
 * Total Submissions: 986.9K
 * Testcase Example:  '[1,8,6,2,5,4,8,3,7]'
 *
 * Given n non-negative integers a1, a2, ..., an , where each represents a
 * point at coordinate (i, ai). n vertical lines are drawn such that the two
 * endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together
 * with x-axis forms a container, such that the container contains the most
 * water.
 *
 * Note: You may not slant the container and n is at least 2.
 *
 *
 *
 *
 *
 * The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In
 * this case, the max area of water (blue section) the container can contain is
 * 49.
 *
 *
 *
 * Example:
 *
 *
 * Input: [1,8,6,2,5,4,8,3,7]
 * Output: 49
 *
 */

#include <iostream>
#include <vector>

#include "tools.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  // 1. 暴力求解，外层遍历数组，内层再次遍历，找到乘积最大的值；
  // 2. 双指针遍历，头尾指针相遇遍历结束，对应较小值的指针向内部移动；
  int maxArea(vector<int>& height) {
    int max_area = 0;
    for (int i = 0, j = height.size() - 1; i < j;) {
#ifdef PRINT_RESULT
      print_result(height, i, -1, j);
#endif
      auto area = (j - i) * min(height[i], height[j]);
      if (area > max_area) {
        max_area = area;
      }
      (height[i] < height[j]) ? i++ : j--;
    }
    return max_area;
  }

  int maxArea2(vector<int>& height) {
    int area_max = 0;
    for (int i = 0; i < height.size() - 1; i++) {
      for (int j = i + 1; j < height.size(); j++) {
        auto area = (j - i) * min(height[i], height[j]);
        if (area > area_max) {
          area_max = area;
        }
      }
    }

    return area_max;
  }

  int maxArea1(vector<int>& height) {
    if (height.size() < 2) {
      return 0;
    }
    int area_max = 0;
    for (int i = 0; i < height.size(); i++) {
      for (int j = height.size() - 1; j > i; j--) {
        auto area = (j - i) * min(height[i], height[j]);
        if (area > area_max) {
          area_max = area;
        }
      }
    }

    return area_max;
  }
};
// @lc code=end

int main() {
  vector<int> arr = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  auto max_area = Solution().maxArea(arr);
  std::cout << max_area << std::endl;
}
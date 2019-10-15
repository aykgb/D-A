/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 *
 * https://leetcode.com/problems/3sum/description/
 *
 * algorithms
 * Medium (24.92%)
 * Likes:    4674
 * Dislikes: 550
 * Total Accepted:    669.1K
 * Total Submissions: 2.7M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * Given an array nums of n integers, are there elements a, b, c in nums such
 * that a + b + c = 0? Find all unique triplets in the array which gives the
 * sum of zero.
 *
 * Note:
 *
 * The solution set must not contain duplicate triplets.
 *
 * Example:
 *
 *
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 *
 * A solution set is:
 * [
 * ⁠ [-1, 0, 1],
 * ⁠ [-1, -1, 2]
 * ]
 *
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include "tools.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  // 1. 暴力求解法3重循环；
  // 2. 排序后，借助2数之和，求3数之和
  // * 集合必须是unique的，不可重复
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    std::sort(nums.begin(), nums.end());
    if (nums.size() < 3 || nums.front() > 0 || nums.back() < 0) {
      return res;
    }
    for (int i = 0; i < nums.size() - 2; i++) {
      if (nums[i] > 0) {
        break;
      }
      if (i > 0 && nums[i] == nums[i - 1]) {  //! 去重
        continue;
      }
      int target = -nums[i];
      int front = i + 1, back = nums.size() - 1;
      while (front < back) {
        if (nums[front] + nums[back] == target) {
          if (front == i + 1 || back == nums.size() - 1) {
            // 当front == i +1 或 back == nums.size() - 1，
            // 说明在固定了nums[i]后，第一次遇到满足条件的情况.
            res.emplace_back(vector<int>{nums[i], nums[front++], nums[back--]});
          } else if (nums[front] == nums[front - 1]) {
            front++;
          } else if (nums[back] == nums[back + 1]) {
            back--;
          } else {
            res.emplace_back(vector<int>{nums[i], nums[front++], nums[back--]});
          }

        } else if (nums[front] + nums[back] < target) {
          front++;
        } else {
          back--;
        }
      }
    }
    return res;
  }

  vector<vector<int>> threeSum4(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() < 3) {
      return res;
    }
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; i++) {
      if (nums[i] > 0) break;  // !剪枝1：排序后nums[i]>0，3数之和必然大于0
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }
      for (int j = i + 1; j < nums.size() - 1; j++) {
        if (j > i + 1 && nums[j] == nums[j - 1]) {
          continue;
        }
        for (int k = j + 1; k < nums.size(); k++) {
          if (k > j + 1 && nums[k] == nums[k - 1]) {
            continue;
          }
          if (nums[i] + nums[j] + nums[k] == 0) {
            res.emplace_back(vector<int>{nums[i], nums[j], nums[k]});
          }
        }
      }
    }

    return res;
  }

  vector<vector<int>> threeSum3(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() < 3) {
      return res;
    }
    std::unordered_map<string, bool> hash_map;  // !去重
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; i++) {
      if (nums[i] > 0) break;  // !剪枝1：排序后nums[i]>0，3数之和必然大于0
      for (int j = i + 1; j < nums.size() - 1; j++) {
        for (int k = j + 1; k < nums.size(); k++) {
          // 存在对称的情况
          // auto solution = std::to_string(nums[i]) + std::to_string(nums[j]) +
          // std::to_string(nums[k]);
          auto solution = std::to_string(nums[i]) + "_" +
                          std::to_string(nums[j]) + "_" +
                          std::to_string(nums[k]);
          if (hash_map.find(solution) != hash_map.end()) {
            continue;
          }
          hash_map.emplace(solution, true);
          if (nums[i] + nums[j] + nums[k] == 0) {
            res.emplace_back(vector<int>{nums[i], nums[j], nums[k]});
          }
        }
      }
    }

    return res;
  }

  vector<vector<int>> threeSum2(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    if (nums.empty() || nums.front() > 0 || nums.back() < 0) return {};

    for (int i = 0; i < nums.size(); i++) {
      int fix = nums[i];
      if (fix > 0) break;
      if (i > 0 && fix == nums[i - 1]) continue;
      //对撞指针
      int l = i + 1, r = nums.size() - 1;
      while (l < r) {
        if (nums[l] + nums[r] == -fix) {
          if (l == i + 1 || r == nums.size() - 1) {
            res.push_back(vector<int>{nums[i], nums[l], nums[r]});
            l++;
            r--;
          } else if (nums[l] == nums[l - 1])
            l++;
          else if (nums[r] == nums[r + 1])
            r--;
          else {
            res.push_back(vector<int>{nums[i], nums[l], nums[r]});
            l++;
            r--;
          }

        } else if (nums[l] + nums[r] < -fix)
          l++;
        else
          r--;
      }
    }
    return res;
  }
};
// @lc code=end

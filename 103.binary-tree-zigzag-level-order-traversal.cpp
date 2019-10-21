/*
 * @lc app=leetcode id=103 lang=cpp
 *
 * [103] Binary Tree Zigzag Level Order Traversal
 *
 * https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * algorithms
 * Medium (43.63%)
 * Likes:    1264
 * Dislikes: 72
 * Total Accepted:    263.8K
 * Total Submissions: 604.3K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, return the zigzag level order traversal of its nodes'
 * values. (ie, from left to right, then right to left for the next level and
 * alternate between).
 *
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 *
 *
 *
 * return its zigzag level order traversal as:
 *
 * [
 * ⁠ [3],
 * ⁠ [20,9],
 * ⁠ [15,7]
 * ]
 *
 *
 */

#include <queue>
#include <stack>
#include <vector>

#include "base_binary_tree.h"

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }
    vector<vector<int>> result;
    std::queue<TreeNode*> queue_node;
    queue_node.push(root);
    bool left2right = true; //!记住遍历顺序
    while (!queue_node.empty()) {
      int level_size = queue_node.size();
      result.emplace_back(vector<int>(level_size));
      for (int i = 0; i < level_size; i++) {
        auto parent = queue_node.front();
        queue_node.pop();
        if (left2right) {
          result.back()[i] = parent->val;
        } else {
          result.back()[level_size - i - 1] = parent->val; //!根据当前level的遍历顺序放入数组
        }
        if(parent->left != nullptr) {
          queue_node.push(parent->left);
        }
        if(parent->right != nullptr) {
          queue_node.push(parent->right);
        }
      }
      left2right ^= true; //!异或操作
    }
    return result;
  }
};
// @lc code=end

int main() { return 0; }
/*
 * @lc app=leetcode id=102 lang=cpp
 *
 * [102] Binary Tree Level Order Traversal
 *
 * https://leetcode.com/problems/binary-tree-level-order-traversal/description/
 *
 * algorithms
 * Medium (50.54%)
 * Likes:    1862
 * Dislikes: 48
 * Total Accepted:    449.6K
 * Total Submissions: 889K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, return the level order traversal of its nodes' values.
 * (ie, from left to right, level by level).
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
 * return its level order traversal as:
 *
 * [
 * ⁠ [3],
 * ⁠ [9,20],
 * ⁠ [15,7]
 * ]
 *
 *
 */
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int val;
  TreeNode(int x) : left(nullptr), right(nullptr), val(x){};
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
  vector<vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }
    std::queue<TreeNode*> queue_node;
    vector<vector<int>> result;
    queue_node.push(root);
    while (!queue_node.empty()) {
      result.emplace_back(vector<int>{});
      int level_size = queue_node.size();
      while(level_size--) {
        auto parent = queue_node.front();
        queue_node.pop();
        result.back().emplace_back(parent->val);
        if (parent->left != nullptr) {
          queue_node.push(parent->left);
        }
        if (parent->right != nullptr) {
          queue_node.push(parent->right);
        }
      }
    }
    return result;
  }

  vector<vector<int>> levelOrder2(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }
    std::queue<TreeNode*> queue_curr_level;
    std::queue<TreeNode*> queue_next_level;
    vector<vector<int>> result;
    queue_curr_level.push(root);
    while (!queue_curr_level.empty()) {
      result.emplace_back(vector<int>{});
      while (!queue_curr_level.empty()) {
        TreeNode* parent = queue_curr_level.front();
        queue_curr_level.pop();
        result.back().emplace_back(parent->val);
        if (parent->left != nullptr) {
          queue_next_level.push(parent->left);
        }
        if (parent->right != nullptr) {
          queue_next_level.push(parent->right);
        }
      }
      queue_next_level.swap(queue_curr_level);
    }
    return result;
  }
};
// @lc code=end

int main() {
  return 0;
}
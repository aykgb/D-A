/*
 * @lc app=leetcode id=144 lang=cpp
 *
 * [144] Binary Tree Preorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-preorder-traversal/description/
 *
 * algorithms
 * Medium (52.96%)
 * Likes:    985
 * Dislikes: 46
 * Total Accepted:    390.5K
 * Total Submissions: 737.2K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the preorder traversal of its nodes' values.
 *
 * Example:
 *
 *
 * Input: [1,null,2,3]
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠   /
 * ⁠  3
 *
 * Output: [1,2,3]
 *
 *
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 *
 */
#include <vector>

#include "base_binary_tree.h"

using namespace std;

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
  /*
   * 非递归解法 - 借助栈 使用vector来模拟栈
   * 前序遍历 根左右
   * 先不断的将访问节点并入栈，直到遇到叶子节点，出栈，并将节点的右子树放入栈中
   */
  vector<int> preorderTraversal(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<int> result;
    vector<TreeNode*> s;
    TreeNode* iter = root;
    while (!s.empty() || iter != nullptr) {
      // 入栈 - 直到遇到空节点，说明访问到最左边界节点
      while (iter != nullptr) {
        result.push_back(iter->val);  // 这里，在入栈过程访问节点值
        s.push_back(iter);
        iter = iter->left;
      }

      // 出栈
      while (!s.empty()) {
        iter = s.back();
        s.pop_back();
        iter = iter->right;
        if (iter != nullptr) {
          // 右子树不为空，跳出回到入栈流程
          break;
        }
      }
    }

    return result;
  }

  // 递归解法 - 深度优先遍历
  vector<int> preorderTraversal2(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }
    vector<int> result;
    preorder(root, result);
    return result;
  }

  void preorder(TreeNode* root, vector<int>& result) {
    if (root == nullptr) {
      return;
    }

    result.emplace_back(root->val);
    preorder(root->left, result);
    preorder(root->right, result);
    return;
  }
};
// @lc code=end

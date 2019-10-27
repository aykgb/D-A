/*
 * @lc app=leetcode id=145 lang=cpp
 *
 * [145] Binary Tree Postorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-postorder-traversal/description/
 *
 * algorithms
 * Hard (50.76%)
 * Likes:    1166
 * Dislikes: 62
 * Total Accepted:    299.6K
 * Total Submissions: 590K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the postorder traversal of its nodes' values.
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
 * Output: [3,2,1]
 *
 *
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 *
 */

#include <iostream>
#include <string>
#include <vector>

#include "base_binary_tree.h"
#include "tools.hpp"

using namespace std;

void print_vec(vector<TreeNode*>& res) {
  for (auto& e : res) {
    std::cout << " " << e->val;
  }
  std::cout << "\n";
}

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
  // 非递归形式 维护一个栈，先将根节点入栈，右节点入栈，后将左节点入栈
  vector<int> postorderTraversal(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }
    vector<int> result;
    vector<TreeNode*> s;
    TreeNode* iter = root;
    TreeNode* iter_prev = nullptr;
    while (!s.empty() || iter != nullptr) {
      // 入栈 - 按左右根的逆序根右左 入栈
      while (iter != nullptr) {
        if (s.empty()) {
          s.push_back(iter);
        }
        if (iter->right != nullptr) {
          s.push_back(iter->right);
        }
        if (iter->left != nullptr) {
          s.push_back(iter->left);
        }
        iter = iter->left;
      }

      // 出栈
      while (!s.empty()) {
        iter = s.back();
        if ((iter->left == nullptr && iter->right == nullptr) ||
            (iter->right != nullptr && iter->right == iter_prev) ||
            (iter->left != nullptr && iter->left == iter_prev)) {
          // 满足出栈条件 - 叶子节点 或 右孩子节点已访问过
          result.push_back(iter->val);
          s.pop_back();
          iter_prev = iter;
        } else {
          // 不满足出栈条件 - 右孩子节点未访问过
          break;
        }
      }

      // 如果这里iter == root 说明已经遍历到了所有节点
      if (iter == root) {
        break;
      }
    }

    return result;
  }

  // 递归算法
  vector<int> postorderTraversal2(TreeNode* root) {
    if (root == nullptr) {
      return {};
    }

    vector<int> result;
    postorder(root, result);
    return result;
  }

  void postorder(TreeNode* root, vector<int>& result) {
    if (root == nullptr) {
      return;
    }
    postorder(root->left, result);
    postorder(root->right, result);
    result.push_back(root->val);
  }
};
// @lc code=end

int main() {
  // vector<string> tree_nodes{"0", "1", "2", "3", "4", "5", "null", "null",
  // "6"}; vector<string> tree_nodes{"1", "null", "2", "3"}; TreeNode* root =
  // create_tree_v2(tree_nodes);
  TreeNode* root = new TreeNode(1);
  root->right = new TreeNode(2);
  root->right->left = new TreeNode(3);

  Solution().postorderTraversal(root);
  destroy_tree(root);

  return 0;
}
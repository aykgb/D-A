/*
 * @lc app=leetcode id=226 lang=cpp
 *
 * [226] Invert Binary Tree
 *
 * https://leetcode.com/problems/invert-binary-tree/description/
 *
 * algorithms
 * Easy (60.13%)
 * Likes:    2135
 * Dislikes: 36
 * Total Accepted:    375.3K
 * Total Submissions: 624.1K
 * Testcase Example:  '[4,2,7,1,3,6,9]'
 *
 * Invert a binary tree.
 *
 * Example:
 *
 * Input:
 *
 *
 * ⁠    4
 * ⁠  /   \
 * ⁠ 2     7
 * ⁠/ \   / \
 * 1   3 6   9
 *
 * Output:
 *
 *
 * ⁠    4
 * ⁠  /   \
 * ⁠ 7     2
 * ⁠/ \   / \
 * 9   6 3   1
 *
 * Trivia:
 * This problem was inspired by this original tweet by Max Howell:
 *
 * Google: 90% of our engineers use the software you wrote (Homebrew), but you
 * can’t invert a binary tree on a whiteboard so f*** off.
 *
 */

#include <stdio.h>

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
  // 递归 - 深度优先遍历
  TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr) {
      return root;
    }
    invert(root);
    return root;
  }

  void invert(TreeNode* root) {
    if (root->left == nullptr && root->right == nullptr) {
      return;
    }
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    if (root->left != nullptr) {
      invert(root->left);
    }
    if (root->right != nullptr) {
      invert(root->right);
    }
    return;
  }
};
// @lc code=end

int main() {
  TreeNode* root = new TreeNode(4);
  root->left = new TreeNode(2);
  root->right = new TreeNode(7);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(9);

  Solution().invertTree(root);

  // TODO: delete tree nodes;

  return 0;
}

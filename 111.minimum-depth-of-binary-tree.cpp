/*
 * @lc app=leetcode id=111 lang=cpp
 *
 * [111] Minimum Depth of Binary Tree
 *
 * https://leetcode.com/problems/minimum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (36.06%)
 * Likes:    881
 * Dislikes: 496
 * Total Accepted:    335.4K
 * Total Submissions: 930K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, find its minimum depth.
 *
 * The minimum depth is the number of nodes along the shortest path from the
 * root node down to the nearest leaf node.
 *
 * Note: A leaf is a node with no children.
 *
 * Example:
 *
 * Given binary tree [3,9,20,null,null,15,7],
 *
 *
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 *
 * return its minimum depth = 2.
 *
 */

#include "base_binary_tree.h"

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
  // 深度优先遍历，分别找到左右子树的深度，并比较大小
  // 对一棵树的深度可分为3中情况： 1. 根节点为空，深度为0；2.
  // 叶子节点，深度为1；3. 中间节点，深度是该节点到左右子树最近节点的的距离
  int minDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
      return 1;
    }
    int left_depth = std::numeric_limits<int>::max();
    int right_depth = left_depth;
    if (root->left != nullptr) {
      left_depth = 1 + minDepth(root->left);  // 根节点到左子树最近节点的距离
    }
    if (root->right != nullptr) {
      right_depth = 1 + minDepth(root->right);  // 跟节点到右子树最近节点的距离
    }
    return min(left_depth, right_depth);  // 比较到左右子树最近节点的距离
  }
};
// @lc code=end
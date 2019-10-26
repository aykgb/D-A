/*
 * @lc app=leetcode id=104 lang=cpp
 *
 * [104] Maximum Depth of Binary Tree
 *
 * https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (62.59%)
 * Likes:    1648
 * Dislikes: 61
 * Total Accepted:    610.2K
 * Total Submissions: 974.8K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, find its maximum depth.
 *
 * The maximum depth is the number of nodes along the longest path from the
 * root node down to the farthest leaf node.
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
 * return its depth = 3.
 *
 */

#include <iostream>
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
  //深度优先，一行代码
  int maxDepth(TreeNode* root) {
    return root == nullptr
               ? 0
               : max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
  }

  //深度优先，携带深度参数
  int maxDepth2(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    int depth = 1;
    int max_depth = 0;
    traversal(root, depth, max_depth);
    return max_depth;
  }

  void traversal(TreeNode* root, int depth, int& max_depth) {
    if (root == nullptr) {
      return;
    }
    if (depth > max_depth) {
      max_depth = depth;
    }
    traversal(root->left, depth + 1, max_depth);
    traversal(root->right, depth + 1, max_depth);
    return;
  }
};
// @lc code=end

int main() {
  vector<string> vals{"3", "9", "20", "null", "null", "15", "7"};
  TreeNode* root = create_tree_v2(vals);
  std::cout << "max depth " << Solution().maxDepth(root) << "\n";
  destroy_tree(root);
  return 0;
}

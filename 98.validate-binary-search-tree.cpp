/*
 * @lc app=leetcode id=98 lang=cpp
 *
 * [98] Validate Binary Search Tree
 *
 * https://leetcode.com/problems/validate-binary-search-tree/description/
 *
 * algorithms
 * Medium (26.51%)
 * Likes:    2524
 * Dislikes: 369
 * Total Accepted:    496.8K
 * Total Submissions: 1.9M
 * Testcase Example:  '[2,1,3]'
 *
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Assume a BST is defined as follows:
 *
 *
 * The left subtree of a node contains only nodes with keys less than the
 * node's key.
 * The right subtree of a node contains only nodes with keys greater than the
 * node's key.
 * Both the left and right subtrees must also be binary search trees.
 *
 *
 *
 *
 * Example 1:
 *
 *
 * ⁠   2
 * ⁠  / \
 * ⁠ 1   3
 *
 * Input: [2,1,3]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * ⁠   5
 * ⁠  / \
 * ⁠ 1   4
 * / \
 * 3   6
 *
 * Input: [5,1,4,null,null,3,6]
 * Output: false
 * Explanation: The root node's value is 5 but its right child's value is 4.
 *
 *
 */
#include <limits>
#include <vector>

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
  // !不能使用广度优先遍历 - 仅仅最小子树合法并不能得到整棵树是合法的BST
  // !不能依赖INT_MIN，而是记录下前驱，并比较
  // 深度优先 - 中序遍历，如果合法，输出递增
  bool isValidBST(TreeNode* root) {
    TreeNode * prev = nullptr;
    return validate(root, prev);
  }

  bool validate(TreeNode* root, TreeNode*& prev) {
      if(root == nullptr) {
          return true;
      }

      if(!validate(root->left, prev)) {
          return false;
      }

      if(prev == nullptr || prev->val < root->val) {
          prev = root;
      } else {
          return false;
      }

      return validate(root->right, prev);
  }
};
// @lc code=end

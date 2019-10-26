#pragma once
#include <functional>
#include <string>
#include <vector>

#include "base_binary_tree.h"

using namespace std;

struct BinTreeNode {
  BinTreeNode *lchild;
  BinTreeNode *rchild;
  BinTreeNode *next;
  int val;

  BinTreeNode(int v) : lchild(nullptr), rchild(nullptr), val(v){};
};

using Visit = std::function<void(BinTreeNode *)>;

BinTreeNode *create_tree(vector<int> &arr, size_t pos = 0);
void destroy_tree(BinTreeNode *root);
void traverse_tree_preorder(BinTreeNode *root, Visit visit);
void traverse_tree_preorder_nonrecursive(BinTreeNode *root, Visit visit);
void traverse_tree_inorder(BinTreeNode *root, Visit visit);
void traverse_tree_inorder_nonrecursive(BinTreeNode *root, Visit visit);
void traverse_tree_postorder(BinTreeNode *root, Visit visit);
void traverse_tree_postorder_nonrecursive(BinTreeNode *root, Visit visit);
void print_tree_graph(BinTreeNode *root);

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *create_tree_v2(vector<string> &arr, size_t pos = 0);
void destroy_tree(TreeNode *root);
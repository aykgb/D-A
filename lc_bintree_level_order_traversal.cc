#include <iostream>
#include <queue>
#include <vector>

#include "base_binary_tree.h"

using namespace std;

class Solution {
 public:
  vector<vector<int>> levelOrder(BinTreeNode* root) {
    std::queue<BinTreeNode*> queue_curr_level;
    std::queue<BinTreeNode*> queue_next_level;
    vector<vector<int>> result;
    int level = 0;
    queue_curr_level.push(root);
    while (!queue_curr_level.empty()) {
      result.emplace_back(vector<int>{});
      while (!queue_curr_level.empty()) {
        BinTreeNode* parent = queue_curr_level.front();
        result[level].emplace_back(parent->val);
        if (parent->lchild != nullptr) {
            queue_next_level.push(parent->lchild);
        }
        if (parent->rchild != nullptr) {
            queue_next_level.push(parent->rchild);
        }
        queue_curr_level.pop();
      }
      level++;
      queue_next_level.swap(queue_curr_level);
    }
    return result;
  }
};

void visit(BinTreeNode* node) { std::cout << node->val << " "; }

int main() {
  vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto root = create_tree(nums);
  auto result = Solution().levelOrder(root);
  auto print_subsets = [&]() {
    std::cout << "[" << std::endl;
    for (auto& subset : result) {
      std::cout << "[";
      for (auto& e : subset) {
        std::cout << e << " ";
      }
      std::cout << "]" << std::endl;
    }
    std::cout << "]" << std::endl;
  };

  print_subsets();

  return 0;
}

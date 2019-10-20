#include <iostream>
#include <queue>
#include <vector>

#include "base_binary_tree.h"

using namespace std;

class Solution {
 public:
  vector<vector<int>> levelOrder(BinTreeNode* root) {
    std::queue<BinTreeNode*> s0;
    std::queue<BinTreeNode*> s1;
    s0.push(root);

    vector<vector<int>> result;
    while (!s0.empty() || !s1.empty()) {
      vector<int> level;
      while (!s0.empty()) {
        auto curr = s0.front();
        level.emplace_back(curr->val);
        s1.push(curr->lchild);
        s1.push(curr->rchild);
        s0.pop();
      }
      result.emplace_back(level);
      level.clear();

      while (!s1.empty()) {
        auto curr = s1.front();
        level.emplace_back(curr->val);
        s0.push(curr->lchild);
        s0.push(curr->rchild);
        s1.pop();
      }
      result.emplace_back(level);
      level.clear();
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

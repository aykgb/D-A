#include <iostream>
#include <vector>
#include <queue>

#include "base_binary_tree.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(BinTreeNode* root) {
        if(root == nullptr) return {};

        vector<vector<int>> result;
        std::queue<BinTreeNode*> node_queue;
        node_queue.push(root);

        bool left2right = true;
        while(!node_queue.empty()) {
            int size = node_queue.size();
            vector<int> level(size);
            for(int i = 0; i < size; i++) {
                auto curr = node_queue.front();
                int pos = left2right ? i : size - i - 1;
                level[pos] = curr->val;
                if(curr->lchild) {
                    node_queue.push(curr->lchild);
                }
                if(curr->rchild) {
                    node_queue.push(curr->rchild);
                }
                node_queue.pop();
            }
            result.emplace_back(level);
            left2right ^= true;
        }

        return result;
    }
};


int main()
{
    vector<int> arr{0, 1, 2, 3, 4, 5, 6};

    BinTreeNode *root = create_tree(arr);

    auto result = Solution().zigzagLevelOrder(root);

    auto print_subsets = [&](){
        std::cout << "[" << std::endl;
        for(auto &subset : result) {
            std::cout << "[";
            for(auto &e : subset) {
                std::cout << e << " ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << "]" << std::endl;
    };

    print_subsets();

    return 0;
}


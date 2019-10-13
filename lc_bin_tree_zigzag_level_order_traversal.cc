#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root == nullptr) return {};

        vector<vector<int>> result;
        std::queue<TreeNode*> node_queue;
        node_queue.push(root);

        bool left2right = true;
        while(!node_queue.empty()) {
            int size = node_queue.size();
            vector<int> level(size);
            for(int i = 0; i < size; i++) {
                auto curr = node_queue.front();
                int pos = left2right ? i : size - i - 1;
                level[pos] = curr->val;
                if(curr->left) {
                    node_queue.push(curr->left);
                }
                if(curr->right) {
                    node_queue.push(curr->right);
                }
                node_queue.pop();
            }
            result.emplace_back(level);
            left2right ^= true;
        }

        return result;
    }
};

TreeNode* create_tree(vector<int>& arr, size_t pos = 0) {
    TreeNode *root = nullptr;
    if(pos < arr.size()) {
        root = new TreeNode(arr[pos]);
        root->left = create_tree(arr, 2 * pos + 1);
        root->right = create_tree(arr, 2 * pos + 2);
    }

    return root;
}


int main()
{
    vector<int> arr{0, 1, 2, 3, 4, 5, 6};

    TreeNode *root = create_tree(arr);

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


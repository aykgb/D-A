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
    vector<vector<int>> levelOrder(TreeNode* root) {
        std::queue<TreeNode*> s0;
        std::queue<TreeNode*> s1;
        s0.push(root);

        vector<vector<int>> result;
        while(!s0.empty() || !s1.empty()) {
            vector<int> level;
            while(!s0.empty()) {
                auto curr = s0.front();
                level.emplace_back(curr->val);
                s1.push(curr->left);
                s1.push(curr->right);
                s0.pop();
            }
            result.emplace_back(level);
            level.clear();

            while(!s1.empty()) {
                auto curr = s1.front();
                level.emplace_back(curr->val);
                s0.push(curr->left);
                s0.push(curr->right);
                s1.pop();
            }
            result.emplace_back(level);
            level.clear();
        }

        return result;
    }
};

int main()
{
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // BST，左节点始终最小，使用中序遍历导出树到数组，然后从左至右累加，再按中序遍历导入到树
    void inorderTraversal_out(TreeNode *root, vector<TreeNode*>& output) {
        if(root != nullptr) {
            inorderTraversal_out(root->left, output);
            output.push_back(root);
            inorderTraversal_out(root->right, output);
        }
    }

    void inorderTraversal(TreeNode *root) {
        if(root != nullptr) {
            inorderTraversal(root->left);
            std::cout << root->val << " ";
            inorderTraversal(root->right);
        }
    }

    TreeNode* convertBST(TreeNode* root) {
        vector<TreeNode*> nodes;
        inorderTraversal_out(root, nodes);
        for(int i = nodes.size() - 2; i > -1; i--) {
            nodes[i]->val += nodes[i+1]->val;
        }

        return root;
    }
};

int main()
{
    vector<int> nums{5, 2, 13};
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right= new TreeNode(13);

    Solution().convertBST(root);
    Solution().inorderTraversal(root);
    std::cout << std::endl;

    delete root->left;
    delete root->right;
    delete root;

    return 0;
}


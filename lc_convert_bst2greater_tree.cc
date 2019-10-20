#include <iostream>
#include <vector>

using namespace std;

struct BinTreeNode {
    int val;
    BinTreeNode *lchild;
    BinTreeNode *rchild;
    BinTreeNode(int x) : val(x), lchild(NULL), rchild(NULL) {}
};

class Solution {
public:
    // BST，左节点始终最小，使用中序遍历导出树到数组，然后从左至右累加，再按中序遍历导入到树
    void inorderTraversal_out(BinTreeNode *root, vector<BinTreeNode*>& output) {
        if(root != nullptr) {
            inorderTraversal_out(root->lchild, output);
            output.push_back(root);
            inorderTraversal_out(root->rchild, output);
        }
    }

    void inorderTraversal(BinTreeNode *root) {
        if(root != nullptr) {
            inorderTraversal(root->lchild);
            std::cout << root->val << " ";
            inorderTraversal(root->rchild);
        }
    }

    BinTreeNode* convertBST(BinTreeNode* root) {
        vector<BinTreeNode*> nodes;
        inorderTraversal_out(root, nodes);
        for(int i = nodes.size() - 2; i > -1; i--) {
            nodes[i]->val += nodes[i+1]->val;
        }

        return root;
    }
};

int main()
{
    vector<int> arr{5, 2, 13};
    BinTreeNode* root = new BinTreeNode(5);
    root->lchild = new BinTreeNode(2);
    root->rchild= new BinTreeNode(13);

    Solution().convertBST(root);
    Solution().inorderTraversal(root);
    std::cout << std::endl;

    delete root->lchild;
    delete root->rchild;
    delete root;

    return 0;
}


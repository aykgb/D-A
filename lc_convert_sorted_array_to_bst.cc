#include <iostream>
#include <vector>

#include "base_binary_tree.h"

using namespace std;

class Solution {
public:
    // 分治法，不断的找根节点
    // len 表示以root为根节点的树，其节点的个数
    // pos 根节点值在数组中的索引
    void preorderTreeBuilder(BinTreeNode* &root, vector<int>& arr, int pos, int len) {
        if(len > 0) {
            root = new BinTreeNode(arr[pos]);
            if(pos == 0 || pos == (int)arr.size()) {
                return;
            }

            int len_lpart = (len - 1) / 2; // (总长 - 根节点个数) / 2
            // 左子树根节点值的相对索引 = (len_lpart - 1) /  2
            // 左子树在数组中的所有元素的起始全局索引 为 pos - len_lpart
            // 起始全局索引 + 相对索引 得到 全局索引
            preorderTreeBuilder(root->lchild, arr, pos - len_lpart + (len_lpart - 1) / 2, len_lpart);

            int len_rpart = (len - 1) - len_lpart;
            // 右子树根节点值的相对索引 = (len_rpart - 1) /  2
            // 右子树在数组中的所有元素的起始全局索引 为 pos + 1
            // 起始全局索引 + 相对索引 得到 全局索引
            preorderTreeBuilder(root->rchild, arr, pos + 1 + (len_rpart  - 1)/ 2, len_rpart);
        }
    }

    void inorderTraversal(BinTreeNode* root) {
        if(root != nullptr) {
            inorderTraversal(root->lchild);
            std::cout << root->val << " ";
            inorderTraversal(root->rchild);
        }
    }

    BinTreeNode* sortedArrayToBST(vector<int>& arr) {
        int len = arr.size();
        BinTreeNode *root = nullptr;
        // 根节点值所在数组中的索引始终是中间或中间偏左的位置。
        preorderTreeBuilder(root, arr, (len - 1) / 2, len);

        return root;
    }
};

int main()
{
    vector<int> sorted { 1, 2, 3, 4, 5, 6, 7 };

    BinTreeNode* root = Solution().sortedArrayToBST(sorted);
    Solution().inorderTraversal(root);
    std::cout << std::endl;

    return 0;
}

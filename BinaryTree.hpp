#include <iostream>
#include <vector>
#include <stack>
#include <functional>
#include <utility>

using namespace std;

struct BinTreeNode {
    int val;
    BinTreeNode *lchild;
    BinTreeNode *rchild;
    BinTreeNode(int v): val(v), lchild(nullptr), rchild(nullptr) {  }
};

using Visit = std::function<void(BinTreeNode *)>;

BinTreeNode* create_tree(vector<int>& arr, size_t pos = 0) {
    BinTreeNode *root = nullptr;
    if(pos < arr.size()) {
        root = new BinTreeNode(arr[pos]);
        root->lchild = create_tree(arr, 2 * pos + 1);
        root->rchild = create_tree(arr, 2 * pos + 2);
    }

    return root;
}

void destroy_tree(BinTreeNode *root) {
    if(root != nullptr) {
        destroy_tree(root->lchild);
        destroy_tree(root->rchild);
        delete root;
    }
}

// 先序遍历
void traverse_tree_preorder(BinTreeNode *root, Visit visit) {
    if(root != nullptr) {
        visit(root);
        traverse_tree_preorder(root->lchild, visit);
        traverse_tree_preorder(root->rchild, visit);
    }
}

void traverse_tree_preorder_nonrecursive(BinTreeNode *root, Visit visit) {
    std::stack<BinTreeNode *> st;
    BinTreeNode* iter = root;
    while(iter != nullptr || !st.empty()) {
        while(iter != nullptr) {
            visit(iter);         // 访问树的根节点
            st.push(iter);       // 将根节点入栈
            iter = iter->lchild;  // 迭代到左子树
        }
        if(!st.empty()) {
            iter = st.top();     // 取栈顶
            st.pop();
            iter = iter->rchild;  // 迭代到右子树
       }
    }
}

// 中序遍历
void traverse_tree_inorder(BinTreeNode *root, Visit visit) {
    if(root != nullptr) {
        traverse_tree_inorder(root->lchild, visit);
        visit(root);
        traverse_tree_inorder(root->rchild, visit);
    }
}

void traverse_tree_inorder_nonrecursive(BinTreeNode *root, Visit visit) {
    std::stack<BinTreeNode *> st;
    BinTreeNode * iter = root;
    while(iter != nullptr || !st.empty()) {
        while(iter != nullptr) { // 找到最左
            st.push(iter);
            iter = iter->lchild;
        }
        if(!st.empty()) {
            iter = st.top();
            visit(iter);
            st.pop();
            iter = iter->rchild; // 当这里迭代到最左的node，iter = iter->rchild 等于空
        }
    }
}

// 后序遍历
void traverse_tree_postorder(BinTreeNode *root, Visit visit) {
    if(root != nullptr) {
        traverse_tree_postorder(root->lchild, visit);
        traverse_tree_postorder(root->rchild, visit);
        visit(root);
    }
}

void traverse_tree_postorder_nonrecursive(BinTreeNode *root, Visit visit) {
    std::stack<BinTreeNode *> st;
    BinTreeNode *iter = nullptr;
    BinTreeNode *iter_pre = nullptr;
    st.push(root);
    while(!st.empty()) {
        iter = st.top();
        /* 如果iter指向的节点左右子树都为空，说明遍历到了叶子节点，可以访问.
         * */
        if((iter->lchild == nullptr && iter->rchild == nullptr) ||
                (iter_pre != nullptr && (iter->lchild == iter_pre || iter->rchild == iter_pre))) {
            visit(iter);
            st.pop();
            iter_pre = iter;
        } else {
            if(iter->rchild != nullptr) {
                st.push(iter->rchild);
            }
            if(iter->lchild != nullptr) {
                st.push(iter->lchild);
            }
        }
    }
}

int test_bin_tree()
{
    vector<int> arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    BinTreeNode *root = create_tree(arr);
    traverse_tree_preorder(root, [](BinTreeNode* node){ std::cout << node->val << " "; });
    std::cout << std::endl;
    traverse_tree_preorder_nonrecursive(root, [](BinTreeNode* node){ std::cout << node->val << " "; });
    std::cout << std::endl;
    traverse_tree_inorder(root, [](BinTreeNode* node){ std::cout << node->val << " "; });
    std::cout << std::endl;
    traverse_tree_inorder_nonrecursive(root, [](BinTreeNode* node){ std::cout << node->val << " "; });
    std::cout << std::endl;
    traverse_tree_postorder(root, [](BinTreeNode* node){ std::cout << node->val << " "; });
    std::cout << std::endl;
    traverse_tree_postorder_nonrecursive(root, [](BinTreeNode* node){ std::cout << node->val << " "; });
    std::cout << std::endl;
    destroy_tree(root);

    return 0;
}

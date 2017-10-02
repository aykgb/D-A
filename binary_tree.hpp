#ifndef _BINARY_TREE_HPP_
#define _BINARY_TREE_HPP_

#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <algorithm>

inline size_t LEFT(size_t pos) { return 2 * pos + 1; }
inline size_t RIGHT(size_t pos) { return 2 * pos + 2; }

/* 二叉树定义底层为链表结构，实现增删查改操作。*/
struct BiTNode
{
    int data;

    BiTNode* lchild;
    BiTNode* rchild;
    BiTNode(int value): data(value), lchild(nullptr), rchild(nullptr) { }
};

// Suppose that the input vector is organized into a binary-tree structrue.
void create_tree(BiTNode*& root, std::vector<int>& arr, size_t pos = 0) {
    if(pos < arr.size()) {
        root = new BiTNode(arr[pos]);
        create_tree(root->lchild, arr, LEFT(pos));
        create_tree(root->rchild, arr, RIGHT(pos));
    }
}

void create_tree2(BiTNode*& root, std::vector<int>& arr, size_t pos = 0) {
    std::queue<BiTNode*> fifo;
    if(pos < arr.size()) {
        root = new BiTNode(arr[pos]);
        fifo.push(root);
    } else {
        return;
    }
    size_t left = arr.size() - 1;
    while(!fifo.empty()) {
        BiTNode* p = fifo.front();
        fifo.pop();
        if(left > 0) {
            p->lchild = new BiTNode(arr[LEFT(pos)]);
            left--;
        } else {
            break;
        }

        if(left > 0) {
            p->rchild = new BiTNode(arr[RIGHT(pos)]);
            left--;
        } else {
            break;
        }
        if(left > 0) {
            fifo.push(p->lchild);
            fifo.push(p->rchild);
        } else {
            break;
        }
        pos++;
    }
}

void create_tree3(BiTNode*& root, std::vector<int>& arr, size_t pos = 0) {
    std::queue<BiTNode*> fifo;
    if(pos < arr.size()) {
        root = new BiTNode(arr[pos]);
        fifo.push(root);
    } else {
        return;
    }
    pos++;
    size_t left = arr.size() - 1;
    while(!fifo.empty()) {
        BiTNode* p = fifo.front();
        fifo.pop();
        if(left > 0) {
            p->lchild = new BiTNode(arr[pos++]);
            left--;
        } else {
            break;
        }
        if(left > 0) {
            p->rchild = new BiTNode(arr[pos++]);
            left--;
        } else {
            break;
        }
        if(left > 0) {
            fifo.push(p->lchild);
            fifo.push(p->rchild);
        } else {
            break;
        }
    }
}

void traverse_preorder(BiTNode* root, std::vector<int>& path) {
    if(root != nullptr) {
        path.push_back(root->data);
        traverse_preorder(root->lchild, path);
        traverse_preorder(root->rchild, path);
    }
}

void traverse_preorder2(BiTNode *root, std::vector<int>& path) {
    std::stack<BiTNode*> s;
    BiTNode *p = root; // 指示指针
    while(p != nullptr || !s.empty()) {
        while(p != nullptr) {
            path.push_back(p->data); // 从左子树开始迭代，迭代左子树的左子树，一直到指示指针为NULL
            s.push(p);
            p = p->lchild;
        }
        if(!s.empty()) {
            p = s.top();
            s.pop();
            p = p->rchild; // 将p指向右子树，对右子树迭代上面的过程
        }
    }
}

void traverse_inorder(BiTNode* root, std::vector<int>& path) {
    if(root != nullptr) {
        traverse_inorder(root->lchild, path);
        path.push_back(root->data);
        traverse_inorder(root->rchild, path);
    }
}

void traverse_inorder2(BiTNode* root, std::vector<int>& path) {
    std::stack<BiTNode*> s;
    BiTNode * p = root;
    while(p != nullptr || !s.empty()) {
        while(p != nullptr) {
            s.push(p);
            p = p->lchild;
        }

        if(!s.empty()) {
            p = s.top();
            s.pop();
            path.push_back(p->data);
            p = p->rchild;
        }
    }
}

void traverse_postorder(BiTNode* root, std::vector<int>& path) {
    if(root != nullptr) {
        traverse_postorder(root->lchild, path);
        traverse_postorder(root->rchild, path);
        path.push_back(root->data);
    }
}

void traverse_postorder2(BiTNode* root, std::vector<int>& path) {
    // the bool indicates that the node is second time showed on the top of stack.
    std::stack<std::pair<BiTNode*, bool>> s;
    BiTNode* p = root;
    while(p != nullptr || !s.empty()) {
        while( p != nullptr ) {
            s.push({p, true}); // it is the first time showed on the top of stack.
            p = p->lchild;
        }

        if(!s.empty()) {
            p = s.top().first;
            bool is_first = s.top().second;
            s.pop();
            if(is_first) {
                s.push({p, false});
                p = p->rchild;
            } else {
                path.push_back(p->data);
                p = nullptr;
            }
        }
    }
}

#endif

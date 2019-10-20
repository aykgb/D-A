#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>

#include "base_binary_tree.h"

using namespace std;

class Solution {
public:
    BinTreeNode* findLegalRoot(BinTreeNode* root, int L, int R) {
        // 移动到合适的根节点
        while(root && root->val > R) {
                root = root->lchild;
        }

        while(root && root->val < L) {
            root = root->rchild;
        }

        return root;
    }

    BinTreeNode* trimBST(BinTreeNode* root, int L, int R) {
        if(root == nullptr) return nullptr;
        if(root->val > R) {
            return trimBST(root->lchild, L, R);
        }
        if(root->val < L) {
            return trimBST(root->rchild, L, R);
        }

        root->lchild = trimBST(root->lchild, L, R);
        root->rchild = trimBST(root->rchild, L, R);

        return root;
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

BinTreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    BinTreeNode* root = new BinTreeNode(stoi(item));
    queue<BinTreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        BinTreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->lchild = new BinTreeNode(leftNumber);
            nodeQueue.push(node->lchild);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->rchild = new BinTreeNode(rightNumber);
            nodeQueue.push(node->rchild);
        }
    }
    return root;
}

int stringToInteger(string input) {
    return stoi(input);
}

string treeNodeToString(BinTreeNode* root) {
    if (root == nullptr) {
      return "[]";
    }

    string output = "";
    queue<BinTreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        BinTreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += to_string(node->val) + ", ";
        q.push(node->lchild);
        q.push(node->rchild);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

int main() {
    string line;
    while (getline(cin, line)) {
        BinTreeNode* root = stringToTreeNode(line);
        getline(cin, line);
        int L = stringToInteger(line);
        getline(cin, line);
        int R = stringToInteger(line);

        BinTreeNode* ret = Solution().trimBST(root, L, R);

        string out = treeNodeToString(ret);
        cout << out << endl;
    }
    return 0;
}

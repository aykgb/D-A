#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void print(ListNode *l) {
    while(l) {
        std::cout << l->val << " ";
        l = l->next;
    }
    std::cout << std::endl;
}

ListNode* mergeTwoLists(ListNode* L1, ListNode* L2) {
    ListNode *pre_head = new ListNode(0);
    ListNode *cur = pre_head;
    while(L1 != nullptr && L2 != nullptr) {
        if(L1->val < L2->val) {
            cur->next = new ListNode(L1->val);
            L1 = L1->next;
        } else {
            cur->next = new ListNode(L2->val);
            L2 = L2->next;
        }
        cur = cur->next;
    }

    // print(pre_head);
    if(L1 != nullptr) {
        cur->next = L1;
    }

    if(L2 != nullptr) {
        cur->next = L2;
    }

    ListNode * result = pre_head->next;
    delete pre_head;

    return result;
}


int main()
{
    ListNode *l1, *l2, *l1_cur, *l2_cur;
    l1 = l2 = l1_cur  = l2_cur = nullptr;
    for(int i = 0; i < 12; i++) {
        if(l1_cur == nullptr) {
            l1 = new ListNode(2 * i);
            l2 = new ListNode(2 * i + 1);
            l1_cur = l1;
            l2_cur = l2;
        } else {
            l1_cur->next = new ListNode(2 * i);
            l2_cur->next = new ListNode(2 * i + 1);
            l1_cur = l1_cur->next;
            l2_cur = l2_cur->next;
        }
    }
    print(l1);
    print(l2);

    ListNode *merged = mergeTwoLists(l1, l2);
    print(merged);

    return 0;
}

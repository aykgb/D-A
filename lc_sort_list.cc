#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int count_size(ListNode* head) {
        int cnt = 0;

        while(head) {
            cnt++;
            head = head->next;
        }

        return cnt;
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode* prehead = new ListNode(0);
        ListNode* l3 = prehead;
        while(l1 && l2) {
            if(l1->val <= l2->val) {
                l3->next = l1;
                l1 = l1->next;
                l3 = l3->next;
            } else {
                l3->next = l2;
                l2 = l2->next;
                l3 = l3->next;
            }
        }

        l1 != nullptr ? l3->next = l1 : l3->next = l2;

        l3 = prehead->next;
        delete prehead;

        return l3;
    }

    ListNode* findNode(ListNode* head, int id) {
        while(id-- && head) {
            head = head->next;
        }
        return head;
    }

    ListNode* sortList(ListNode* head) {
        if(head == nullptr) return head;

        int len = count_size(head);
        if(len == 1) return head;

        ListNode* tail = head;
        while(tail->next) {
            tail = tail->next;
        }

        if(head != tail) {
            ListNode* head_lpart = head;
            ListNode* middle = findNode(head, len / 2 - 1);
            ListNode* head_rpart = middle->next;
            middle->next = nullptr;
            head_lpart = sortList(head_lpart);
            head_rpart = sortList(head_rpart);
            head = merge(head_lpart, head_rpart);
        }

        return head;
    }

    struct LessCompare {
        bool operator()(ListNode* n1, ListNode* n2) const {
            return n1->val < n2->val;
        }
    } compare;

    ListNode* sortList2(ListNode* head) {
        vector<ListNode*> node_arr;
        while(head) {
            node_arr.push_back(head);
            head = head->next;
        }

        std::sort(node_arr.begin(), node_arr.end(), compare);

        ListNode *prehead = new ListNode(0);
        head = prehead;
        for(auto &e : node_arr) {
            head->next = e;
            head = head->next;
        }
        head->next = nullptr;

        head = prehead->next;
        delete prehead;

        return head;
    }
};

ListNode* create_list(vector<int>&& nums) {
    ListNode *head = new ListNode(0);
    ListNode *t = head;
    for(auto & e: nums) {
        t->next = new ListNode(e);
        t = t->next;
    }
    t = head;
    head = head->next;
    delete t;

    return head;
}

void destroy_list(ListNode*& head) {
    while(head) {
        ListNode* t = head;
        head = head->next;
        delete t;
    }
}

int main()
{
    vector<int> nums {2, 1};
    ListNode *head = create_list(std::move(nums));
    auto print_list = [](ListNode *head) {
        while(head) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
    };

    print_list(head);
    head = Solution().sortList2(head);
    print_list(head);

    ListNode *l1 = create_list({0, 2, 4, 6, 7, 9});
    ListNode *l2 = create_list({1, 3, 5, 7, 12});
    ListNode *l3 = Solution().merge(l1, l2);
    print_list(l3);

    destroy_list(l3);
    destroy_list(head);

    return 0;
}

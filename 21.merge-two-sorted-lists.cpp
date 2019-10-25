/*
 * @lc app=leetcode id=21 lang=cpp
 *
 * [21] Merge Two Sorted Lists
 *
 * https://leetcode.com/problems/merge-two-sorted-lists/description/
 *
 * algorithms
 * Easy (49.44%)
 * Likes:    2789
 * Dislikes: 408
 * Total Accepted:    721.3K
 * Total Submissions: 1.5M
 * Testcase Example:  '[1,2,4]\n[1,3,4]'
 *
 * Merge two sorted linked lists and return it as a new list. The new list
 * should be made by splicing together the nodes of the first two lists.
 *
 * Example:
 *
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
 *
 *
 */

#include "base_linked_list.h"

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy_head(0);
    ListNode* tail = &dummy_head;
    while(l1 != nullptr && l2 != nullptr) {
        if(l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    if(l1 != nullptr) {
        tail->next = l1;
    }
    if(l2 != nullptr) {
        tail->next = l2;
    }
    return dummy_head.next;
  }
};
// @lc code=end

int main() {
  vector<int> nums1{1, 4, 5};
  vector<int> nums2{2, 3, 6, 7};
  ListNode *l1= create_list(nums1);
  ListNode *l2= create_list(nums2);
  ListNode *head = Solution().mergeTwoLists(l1, l2);
  print_list_pretty(head);
  destory_list(head);
}


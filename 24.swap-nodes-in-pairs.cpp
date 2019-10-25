/*
 * @lc app=leetcode id=24 lang=cpp
 *
 * [24] Swap Nodes in Pairs
 *
 * https://leetcode.com/problems/swap-nodes-in-pairs/description/
 *
 * algorithms
 * Medium (46.76%)
 * Likes:    1465
 * Dislikes: 133
 * Total Accepted:    368K
 * Total Submissions: 786K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * You may not modify the values in the list's nodes, only nodes itself may be
 * changed.
 *
 *
 *
 * Example:
 *
 *
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
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
  // 交换节点的值；
  ListNode *swapPairs(ListNode *head) {
    if(head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode* node_curr = head;
    ListNode* node_next = head->next;
    while(node_curr != nullptr && node_next != nullptr) {
      std::swap(node_curr->val, node_next->val);
      node_curr = node_next->next;
      if(node_curr != nullptr) {
        node_next = node_curr->next;
      }
    }
    return head;
  }

  // 纯交换节点；
  ListNode *swapPairs2(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }
    ListNode *new_head = head->next;
    ListNode *node_prev = nullptr;
    ListNode *node_curr = head;
    ListNode *node_next = node_curr->next;
    node_curr->next = node_next->next;
    node_next->next = node_curr;
    node_prev = node_curr;
    node_curr = node_curr->next;
    if (node_curr != nullptr) {
      node_next = node_curr->next;
    } else {
      return new_head;
    }
    while (node_next != nullptr) {
      node_prev->next = node_next;
      node_curr->next = node_next->next;
      node_next->next = node_curr;
      node_prev = node_curr;
      node_curr = node_curr->next;
      if (node_curr == nullptr) {
        break;
      }
      node_next = node_curr->next;
    }

    return new_head;
  }
};
// @lc code=end

int main() {
  vector<int> nums{1, 2, 3, 4, 5, 6};
  ListNode *head = create_list(nums);
  print_list_pretty(head);
  head = Solution().swapPairs(head);
  print_list_pretty(head);
  destory_list(head);
}

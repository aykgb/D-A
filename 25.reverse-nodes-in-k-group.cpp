/*
 * @lc app=leetcode id=25 lang=cpp
 *
 * [25] Reverse Nodes in k-Group
 *
 * https://leetcode.com/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (38.23%)
 * Likes:    1461
 * Dislikes: 295
 * Total Accepted:    213.1K
 * Total Submissions: 556.4K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 *
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes in the end should remain as it is.
 *
 *
 *
 *
 * Example:
 *
 * Given this linked list: 1->2->3->4->5
 *
 * For k = 2, you should return: 2->1->4->3->5
 *
 * For k = 3, you should return: 3->2->1->4->5
 *
 * Note:
 *
 *
 * Only constant extra memory is allowed.
 * You may not alter the values in the list's nodes, only nodes itself may be
 * changed.
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
  // 直接遍历链表，将链表节点插入新链表合适的位置
  ListNode* reverseKGroup3(ListNode* head, int k) {
    if (head == nullptr || k == 1) {
      return head;
    }
    ListNode dummy_head(-1);
    dummy_head.next = head;
    ListNode *curr = &dummy_head, *next, *prev = curr;
    int len = 0;
    // 计算链表的长度
    while (curr = curr->next) {
      len++;
    }
    while (len >= k) {
      curr = prev->next;
      next = curr->next;
      for (int i = 0; i < k - 1; i++) {  //!只需要反转k-1次
        curr->next = next->next;
        next->next = prev->next;
        prev->next = next;
        next = curr->next;
      }
      prev = curr;
      len -= k;
    }
    return dummy_head.next;
  }
  // 使用一个size为k的数组按顺序存放节点的值，再对节点顺序遍历，逆序赋值
  ListNode* reverseKGroup(ListNode* head, int k) {
    int idx = 0;
    vector<int> vals(k);
    ListNode* n0 = head;
    ListNode* n1 = head;
    while (n1 != nullptr) {
      vals[idx++] = n1->val;
      if (idx == k) {
        while (idx--) {
          n0->val = vals[idx];
          n0 = n0->next;
        }
        idx = 0;
      }
      n1 = n1->next;
    }
    return head;
  }
  // 不断翻转长度为k的链表，并给出翻转的的子链表的头结点和尾节点用于下次翻转输入和链表的连接
  ListNode* reverseKGroup2(ListNode* head, int k) {
    if (k < 2 || head == nullptr || head->next == nullptr) {
      return head;
    }
    if (countListLength(head) < k) {
      return head;
    }
    auto result = reverseOneGroup(head, k);
    auto result_next = result;
    head = result.first;
    while (result.second != nullptr && result.second->next != nullptr) {
      result_next = reverseOneGroup(result.second->next, k);
      result.second->next = result_next.first;
      result.swap(result_next);
    }
    if (isLastGroup(result.first, k)) {
      result = reverseOneGroup(result.first, k);
      result_next.second->next = result.first;
    }

    return head;
  }

  std::pair<ListNode*, ListNode*> reverseOneGroup(ListNode* head, int k) {
    ListNode* group_head = head;
    ListNode* group_tail = head;
    head = head->next;
    group_tail->next = nullptr;
    while (head != nullptr) {
      ListNode* node = head;
      head = head->next;
      node->next = group_head;
      group_head = node;
      if (--k == 1) {
        break;
      }
    }
    group_tail->next = head;
    return std::pair<ListNode*, ListNode*>(group_head, group_tail);
  }

  int isLastGroup(ListNode* head, int k) {
    while (head != nullptr) {
      head = head->next;
      k--;
    };
    return k;
  }

  int countListLength(ListNode* head) {
    int count = 0;
    while (head != nullptr) {
      count++;
      head = head->next;
    }
    return count;
  }
};
// @lc code=end

int main() {
  vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  auto head = create_list(nums);
  print_list_pretty(head);
  head = Solution().reverseKGroup3(head, 5);
  print_list_pretty(head);
  destory_list(head);

  return 0;
}

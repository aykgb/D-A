/*
 * @lc app=leetcode id=206 lang=cpp
 *
 * [206] Reverse Linked List
 *
 * https://leetcode.com/problems/reverse-linked-list/description/
 *
 * algorithms
 * Easy (57.42%)
 * Likes:    2950
 * Dislikes: 73
 * Total Accepted:    717.2K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * Reverse a singly linked list.
 *
 * Example:
 *
 *
 * Input: 1->2->3->4->5->NULL
 * Output: 5->4->3->2->1->NULL
 *
 *
 * Follow up:
 *
 * A linked list can be reversed either iteratively or recursively. Could you
 * implement both?
 *
 */
#include <iostream>

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
  // 1. 使用一个stack
  // 2. 使用一个辅助链表，不断的从头部插入
  ListNode* reverseList(ListNode* head) {
    if (head == nullptr) {
      return head;
    }

    // 初始化，将head结点赋给新链表的头结点，移动head，并将新链表的头结点next指针赋空
    ListNode* new_head = head;
    head = head->next;
    new_head->next = nullptr;
    // 不断将链表的节点插入到新链表的头部
    while (head != nullptr) {
      // 取节点
      ListNode* node = head;
      head = head->next;
      // 将节点加入新链表的头部
      node->next = new_head;
      new_head = node;
    }
    return new_head;
  }
};
// @lc code=end

int main() { return 0; }
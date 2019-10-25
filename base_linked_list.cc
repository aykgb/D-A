#include <iostream>
#include <vector>

#include "include/base_linked_list.h"

ListNode* create_list(vector<int>& nums) {
  if (nums.size() < 1) {
    return nullptr;
  }
  ListNode head_dummy(0);
  ListNode* node = &head_dummy;
  for (auto& ele : nums) {
    node->next = new ListNode(ele);
    node = node->next;
  }
  return head_dummy.next;
}

void destory_list(ListNode* head) {
  while (head != nullptr) {
    ListNode *node = head;
    head = head->next;
    delete(node);
  }
}

void print_list_pretty(ListNode* head) {
  std::cout << "head -> ";
  while(head->next != nullptr) {
    std::cout << head->val << " ->";
    head = head->next;
  }
  std::cout << " " << head->val << "\n";
}
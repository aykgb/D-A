/*
 * @lc app=leetcode id=142 lang=cpp
 *
 * [142] Linked List Cycle II
 *
 * https://leetcode.com/problems/linked-list-cycle-ii/description/
 *
 * algorithms
 * Medium (33.85%)
 * Likes:    1796
 * Dislikes: 146
 * Total Accepted:    248.3K
 * Total Submissions: 732.3K
 * Testcase Example:  '[3,2,0,-4]\n1'
 *
 * Given a linked list, return the node where the cycle begins. If there is no
 * cycle, return null.
 *
 * To represent a cycle in the given linked list, we use an integer pos which
 * represents the position (0-indexed) in the linked list where tail connects
 * to. If pos is -1, then there is no cycle in the linked list.
 *
 * Note: Do not modify the linked list.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: head = [3,2,0,-4], pos = 1
 * Output: tail connects to node index 1
 * Explanation: There is a cycle in the linked list, where tail connects to the
 * second node.
 *
 *
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,2], pos = 0
 * Output: tail connects to node index 0
 * Explanation: There is a cycle in the linked list, where tail connects to the
 * first node.
 *
 *
 *
 *
 * Example 3:
 *
 *
 * Input: head = [1], pos = -1
 * Output: no cycle
 * Explanation: There is no cycle in the linked list.
 *
 *
 *
 *
 *
 *
 * Follow-up:
 * Can you solve it without using extra space?
 *
 */

#include <iostream>
#include <unordered_map>
#include <vector>

#include "base_linked_list.h"

using namespace std;
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
  // 遍历链表，节点指针为key，每遍历到一个节点1次计数加1，找到第一个计数为2的节点即为入口节点
  ListNode *detectCycle(ListNode *head) {
    unordered_map<ListNode *, int> mapNode2Counter;
    while (head != nullptr) {
      if (++mapNode2Counter[head] > 1) {
        break;
      }
      head = head->next;
    }
    return head;
  }
  // 快慢指针找到第一次相遇点，然后从头和相遇点以同等的速度移动指针，相遇点即为入口点
  ListNode *detectCycle2(ListNode *head) {
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast != nullptr && fast->next != nullptr) {
      fast = fast->next->next;
      slow = slow->next;
      if (fast == slow) {
        break;
      }
    }
    if (fast == nullptr || fast->next == nullptr) {
      return nullptr;
    }
    slow = head;
    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }
    return slow;
  }
};
// @lc code=end

int main() {
  auto nums = vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto head = create_list(nums);
  auto tail = head;
  while (tail->next != nullptr) {
    tail = tail->next;
  }
  auto node = head->next->next->next->next;
  tail->next = node;
  node = Solution().detectCycle(head);
  std::cout << node->val << std::endl;
}

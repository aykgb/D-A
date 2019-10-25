#pragma once

#include <string>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* create_list(vector<int>& nums);
void destory_list(ListNode* head);
void print_list_pretty(ListNode* head);


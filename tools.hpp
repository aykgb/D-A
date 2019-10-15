#pragma once

#include <iostream>
#include <vector>

using namespace std;
const int MAX_DISPLAY_SIZE = 20;

static bool enable_print_result = false;

void EnablePrintResult() { enable_print_result = true; }

void print_result(vector<int>& arr, int begin, int pos, int end) {
  if (!enable_print_result) {
    return;
  }
  if (arr.size() > MAX_DISPLAY_SIZE) {
    return;
  }
  static int count;
  if (pos == -1) {
    count = 0;
  }
  printf("%2d@ ", count);
  for (auto i = 0; i < arr.size(); i++) {
    if (i == begin) {
      std::cout << "( ";
    }
    if (i != pos) {
      std::cout << arr[i] << " ";
    } else {
      std::cout << "[" << arr[i] << "] ";
    }
    if (i + 1 == end) {
      std::cout << ") ";
    }
  }
  printf("  #begin:%d pos:%d end:%d", begin, pos, end);
  count++;
  std::cout << endl;
}

void print_result_summary(vector<int>& arr) {
  printf("result: ");
  if (arr.size() <= MAX_DISPLAY_SIZE) {
    for (auto i = 0; i < arr.size(); i++) {
      std::cout << arr[i] << " ";
    }
  } else {
    for (auto i = 0; i < MAX_DISPLAY_SIZE / 2; i++) {
      std::cout << arr[i] << " ";
    }
    std::cout << " ... ";
    for (auto i = 0; i < MAX_DISPLAY_SIZE / 2; i++) {
      std::cout << arr[arr.size() - 10 + i] << " ";
    }
  }
  std::cout << "\n\n";
}

#include <chrono>
#include <iostream>
#include <vector>
#include "tools.hpp"

using namespace std;

/**
 * 1. 合并2个已排序的数组；
 * 2. 对一个未排序的数组使用分治，不断划分，直到划分为两两一组。
 * 3. note: 使用原位插入的方法，不使用额外的空间
 */

// 如对 4 7 8  1 3 3 beg:0 endbeg:3 end:6
void merge_sorted_array(vector<int>& arr, int beg, int endbeg, int end) {
  vector<int> result;  // !使用result，结果算出后回填arr
  int li = beg, ri = endbeg;
  while (true) {
    if (li < endbeg && arr[li] <= arr[ri]) {
      result.push_back(arr[li++]);
      continue;
    }
    if (ri < end && arr[ri] < arr[li]) {
      result.push_back(arr[ri++]);
      continue;
    }
    if (li != endbeg - 1 || ri != end - 1) {
      // !后置，当有任意数组迭代完所有元素跳出
      break;
    }
  }
  // 填充剩余元素
  while (li < endbeg) result.push_back(arr[li++]);
  while (ri < end) result.push_back(arr[ri++]);
  // 将结果回填数组
  for (int i = 0; i < result.size(); i++) {
    arr[beg + i] = result[i];
  }
  print_result(arr, beg, (beg + end) / 2, end);
}

void merge_sort(vector<int>& arr, int beg, int end) {
  if (end - beg == 1) {  // !只剩下一个元素，递归结束
    return;
  }
  merge_sort(arr, beg, (beg + end) / 2);
  merge_sort(arr, (beg + end) / 2, end);
  merge_sorted_array(arr, beg, (beg + end) / 2, end);
}

void test_merge_sort(int length, int method = 1) {
  vector<int> arr;
  for (auto i = 0; i < length; i++) {
    auto e = std::rand() % length;
    arr.emplace_back(e);
  }
  print_result(arr, 0, -1, arr.size());

  auto start = std::chrono::steady_clock().now();
  if (method == 1) {
    merge_sort(arr, 0, arr.size());
  } else if (method == 2) {
    // select_sort(arr);
  } else {
    // insert_sort(arr);
  }
  auto duration = std::chrono::steady_clock().now() - start;
  printf("merge sort method %d total %d elements cost %lld.%03lld seconds\n",
         method, length, duration / chrono::seconds(1),
         duration % chrono::seconds(1) / chrono::milliseconds(1));

  print_result_summary(arr);
  return;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "parameter error.\n";
    return -1;
  }
  auto para = argv[1];
  auto size = std::stoi(string(para));

  test_merge_sort(size);
}
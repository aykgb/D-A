#pragma once

#include <iostream>
#include <vector>

using namespace std;

// 冒泡排序
void bubble_sort(vector<int>& arr) {
  int len = arr.size();
  bool swaped = false;
  for (int i = 0; i < len - 1; i++) {  //! 只需要迭代到前len-1个元素
    for (int j = 0; j < len - i - 1; j++) {
     if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        swaped = true;
      }
    }

    if (!swaped) {  // 如果其中有一次未发生交换，说明已经完全排序好了
      break;
    }
    swaped = false;
  }
}

// 将数组划分为排序和未排序部分
// 从未排序部分取出一个数，插入到排序部分的合适位置
// 初始时认为第一个元素是排序的部分
void insert_sort(vector<int>& arr) {
  int len = arr.size();
  int i = 0, j = i + 1;  // i指向已排序部分的尾部，j指向未排序部分头部
  while (i < len - 1 && j < len) {
    int to_be_sorted = arr[j];
    int k = j;
    for (; k > 0 && arr[k - 1] > to_be_sorted; k--) {
      arr[k] = arr[k - 1];
    }
    arr[k] = to_be_sorted;
    i++;
    j++;
  }
}

void insert_sort2(vector<int>& arr) {
  int len = arr.size();
  // 对N个元素，当N-1个元素插入合适的位置，那么整个数组就排序完成
  for (int i = 0; i < len - 1; i++) {  // i仅表示迭代号
    int j = i + 1;  // j指向未排序部分首元素，那么j-1就是排序部分尾元素
    int unsorted = arr[j];
    while (unsorted < arr[j - 1] && j > 0) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = unsorted;
  }
}

// 每次选取未排序部分中最大/最小的元素放入合适的位置
void select_sort(vector<int>& arr) {
  int len = arr.size();
  // 对N个元素，当N-1个元素都放入正确的位置时，那么整个数组就排序完成
  for (int i = 0; i < len - 1; i++) {  // i仅表示迭代号
    // 找到最大元素所在的位置
    int max_pos = 0;
    for (int j = 0; j < len - i; j++) {
      if (arr[j] > arr[max_pos]) {
        max_pos = j;
      }
    }
    std::swap(arr[max_pos], arr[len - i - 1]);
    // 如：对第0次迭代，找到最大的数后，放到len - 1索引指向的位置
  }
}

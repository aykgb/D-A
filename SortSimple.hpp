#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace SortSimple{
// 冒泡排序
void bubble_sort(vector<int>& nums) {
    int len = nums.size();
    for(int i = 0; i < len; i++) {
        for(int j = len - 1; j > i; j--) {
            if(nums[j - 1] > nums[j]) {
                std::swap(nums[j - 1], nums[j]);
            }
        }
    }
}

void bubble_sort2(vector<int>& nums) {
    int len = nums.size();
    // 只需要迭代N-1次，将N-1个元素排好序了，那么整个数组就排好序了
    for(int i = 0; i < len - 1; i++) {
        for(int j = 0; j < len - i - 1; j++) { // len - i - 1是预留的位置，所以j < len - i;
            if(nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
            }
        }
    }
}

void bubble_sort3(vector<int>& nums) {
    int len = nums.size();
    bool swaped = false;
    for(int i = 0; i < len - 1; i++) {
        for(int j = 0; j < len - i - 1; j++) {
            if(nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
                swaped = true;
            }
        }

        if(!swaped) { // 如果其中有一次未发生交换，说明已经完全排序好了
            break;
        }
        swaped = false;
    }
}

// 将数组划分为排序和未排序部分
// 从未排序部分取出一个数，插入到排序部分的合适位置
// 初始时认为第一个元素是排序的部分
void insert_sort(vector<int>& nums) {
    int len = nums.size();
    int i = 0, j = i + 1; // i指向已排序部分的尾部，j指向未排序部分头部
    while(i < len - 1 && j < len) {
        int to_be_sorted = nums[j];
        int k = j;
        for(; k > 0 && nums[k - 1] > to_be_sorted; k--) {
            nums[k] = nums[k - 1];
        }
        nums[k] = to_be_sorted;
        i++;
        j++;
    }
}

void insert_sort2(vector<int>& nums) {
    int len = nums.size();
    // 对N个元素，当N-1个元素插入合适的位置，那么整个数组就排序完成
    for(int i = 0; i < len - 1; i++) {  // i仅表示迭代号
        int j = i + 1; // j指向未排序部分首元素，那么j-1就是排序部分尾元素
        int unsorted = nums[j];
        while(unsorted < nums[j - 1] && j > 0) {
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j] = unsorted;
    }
}

// 每次选取未排序部分中最大/最小的元素放入合适的位置
void select_sort(vector<int>& nums) {
    int len  = nums.size();
    // 对N个元素，当N-1个元素都放入正确的位置时，那么整个数组就排序完成
    for(int i = 0; i < len - 1; i++) {  // i仅表示迭代号
        // 找到最大元素所在的位置
        int max_pos = 0;
        for(int j = 0; j < len - i; j++) {
            if(nums[j] > nums[max_pos]) {
                max_pos = j;
            }
        }
        std::swap(nums[max_pos], nums[len - i - 1]);
        // 如：对第0次迭代，找到最大的数后，放到len - 1索引指向的位置
    }
}

}


#pragma once

#include <iostream>
#include <vector>

using namespace std;

// 算法导论版
namespace SortQuick{
int partition(vector<int>& nums, int head, int tail) {
    int id = head + std::rand() % (tail - head + 1);
    std::swap(nums[id], nums[tail]);

    int pivot = nums[tail];
    int j = head - 1;
    for(int i = head; i < tail; i++) {
        if(nums[i] <= pivot) {
            j++;
            if(i != j) { // 10W次单机性能优化明显
                std::swap(nums[i], nums[j]);
            }
        }
    }

    std::swap(nums[j + 1], nums[tail]);
    return j + 1;
}

#if 0 // 实现起来太困难，本质上是在原partition的基础上增加partition的倒索引遍历
// 头尾双指针法
int partition1(vector<int>& nums, int head, int tail) {
    /* 随机生成一个索引，将该索引指向的元素作为枢纽元pivot。 */
    int id = head + std::rand() % (tail - head + 1);
    int pivot = nums[id];
    /* 将枢纽元(pivot)交换到数组头部 */
    std::swap(nums[id], nums[tail]);
    /* 迭代 */
    while(head < tail) {
        while(nums[head] < pivot && head < tail) head++;
        while(nums[tail] >= pivot && head < tail) tail--; // 把等于枢纽元的元素分割到到右半部分，所以最后不需要对枢纽元交换？
        std::swap(nums[head + 1], nums[tail]);
    }
    return head; // 返回左半部分最后一个元素的索引
}
#endif


void quick_sort(vector<int>& nums, int head, int tail) {
    if(head < tail) {
        int p = partition(nums, head, tail);
        // int p = partition1(nums, head, tail);
        quick_sort(nums, head, p - 1); // 位置p是排好序的，所以跳过p
        quick_sort(nums, p + 1, tail);// 位置p是排好序的，所以跳过p
    }
}

}


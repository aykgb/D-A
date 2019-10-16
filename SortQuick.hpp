#pragma once

#include <iostream>
#include <vector>

using namespace std;

// 算法导论版
namespace SortQuick{
int partition(vector<int>& nums, int head, int tail) {
    if(head > tail) return -1;
    if(head == tail) return head;
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

// 头尾双指针法，单机测试10w数据情况下比上面的partition快10%左右
int partition1(vector<int>& nums, int head, int tail) {
    if(head > tail) return -1;
    if(head == tail) return head;
    /* 随机生成一个索引，将该索引指向的元素作为枢纽元pivot。 */
    int id = head + std::rand() % (tail - head + 1);
    int pivot = nums[id];
    /* 将枢纽元(pivot)交换到数组头部 */
    std::swap(nums[id], nums[tail]);

    int i = head, j = tail - 1;
    if(i == j) { // i j相遇即返回
        if(nums[i] <= pivot) {
            return  i + 1;
        } else {
            std::swap(nums[i], nums[tail]);
            return i;
        }
    }

    /* 迭代 */
    while(i < j) {
        while(nums[i] <= pivot && i < j) {
            i++;
            if(i == j) { // i j相遇即返回
                if(nums[i] <= pivot) {
                    std::swap(nums[i + 1], nums[tail]);
                    return  i + 1;
                } else {
                    std::swap(nums[i], nums[tail]);
                    return i;
                }
            }
        }

        while(nums[j] > pivot && i < j) {
            j--;
            if(i == j) { // i j相遇即返回
                if(nums[i] <= pivot) {
                    std::swap(nums[i + 1], nums[tail]);
                    return i + 1;
                } else {
                    std::swap(nums[i], nums[tail]);
                    return i;
                }
            }
        }

        std::swap(nums[i], nums[j]);
    }

    return -1; // invalid case.
}


void quick_sort(vector<int>& nums, int head, int tail) {
    if(head < tail) {
        // int p = partition(nums, head, tail);
        int p = partition1(nums, head, tail);
        quick_sort(nums, head, p - 1); // 位置p是排好序的，所以跳过p
        quick_sort(nums, p + 1, tail);// 位置p是排好序的，所以跳过p
    }
}

}


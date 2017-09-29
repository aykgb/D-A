#ifndef _HEAP_SORT_HPP_
#define _HEAP_SORT_HPP_

#include <utility>

void max_heapify(int A[], int length, int i)  //维护
{
    int left = i * 2 + 1;  //节点i的左孩子
    int right = left + 1; //节点i的右孩子节点
    int largest = i;  //默认父节点
    if (left <= length && A[largest] < A[left])  //左孩子比父节点大
    {
        largest = left;
    }
    if (right <= length && A[largest] < A[right])  //右孩子最大
    {
        largest = right;
    }
    if (i != largest)   //最大值不是父节点
    {
        std::swap(A[i], A[largest]);
        max_heapify(A, length, largest);  //继续维护
    }
}

void build_max_heap(int A[], int length)  //建堆
{
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        max_heapify(A, length, i);
    }
}

void heap_sort(int A[], int length)  //堆排
{
    build_max_heap(A, length);      //建堆
    for(int i = length; i >= 1;)  //最后一个肯定是最小的
    {
        std::swap(A[i], A[0]);

        i--;        //堆的大小减一
        max_heapify(A, i, 0);  //调堆
    }
}

#endif

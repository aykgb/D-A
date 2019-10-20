#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace SortHeap {
/*   parent: 根节点索引
 *   tail:   最后一个叶子节点索引，结尾点
 *   自顶向下调整
 */
void adjust_max(std::vector<int>& arr, int parent, int tail) {
    int lchild = 2 * parent + 1;
    int rchild = 2 * parent + 2;
    int largest = parent;
    if(lchild <= tail && arr[lchild] > arr[largest]) {
        largest = lchild;
    }
    if(rchild <= tail && arr[rchild] > arr[largest]) {
        largest = rchild;
    }
    if(parent != largest) {
        std::swap(arr[parent], arr[largest]);
        adjust_max(arr, largest, tail);
    }
}

/*   parent: 根节点索引
 *   tail:    最后一个叶子节点索引
 */
void adjust_max1(std::vector<int>& arr, int parent, int tail) {
    while(true) {
        int lchild = parent * 2 + 1;
        int rchild = parent * 2 + 2;
        int largest = parent;
        if(lchild <= tail && arr[lchild] > arr[largest]) {
            largest = lchild;
        }
        if(rchild <= tail && arr[rchild] > arr[largest]) {
            largest = rchild;
        }
        if(largest != parent) {
            std::swap(arr[largest], arr[parent]);
            parent = largest;
        } else {
            break;
        }
    }
}

/*   parent: 根节点索引
 *   tail:    最后一个叶子节点索引
 */
void adjust_min(vector<int>& arr, int parent, int tail) {
    while(true) {
        int lchild = parent * 2 + 1;
        int rchild = parent * 2 + 2;
        int smallest = parent;
        if(lchild <= tail && arr[smallest] > arr[lchild]) {
            smallest = lchild;
        }
        if(rchild <= tail && arr[smallest] > arr[rchild]) {
            smallest = rchild;
        }
        if(smallest != parent) {
            std::swap(arr[parent], arr[smallest]);
            parent = smallest; // 向下迭代
        } else {
            break;
        }
    }
}

// 自底向上，建完堆后，只需要一次adjust即可找到最大/小元素
void build_max_heap(vector<int>& arr) {
    int len = arr.size();
    for(int i = len / 2 - 1; i > -1; i--) {
        adjust_max(arr, i, len);
    }
}

void build_min_heap(vector<int>& arr) {
    int len = arr.size();
    for(int i = len / 2 - 1; i > -1; i--) {
        adjust_min(arr, i, len);
    }
}

void heap_sort(vector<int>& arr) {
#if 1
    int tail = arr.size() - 1;
    build_max_heap(arr);
    std::swap(arr[0], arr[tail]);
    tail--;
    while(tail > 0) {
        adjust_max(arr, 0, tail);
        std::swap(arr[0], arr[tail--]);
    }
#else
    // 这种排序方式是错误的，因为取出最小堆堆顶的方式破坏了原有的堆的结构
    // 所以在数组上的堆的构建必须要有交换这一步骤
    for(size_t i = 0; i < arr.size(); i++) {
        build_min_heap(arr, i, arr.size() - 1);
    }
#endif
}

}

int test_heap_sort()
{
    vector<int> arr{-1, 3, 2, 0, -5, 6, 9, -2, 10, -29, 32, 1, 7};
    std::for_each(arr.begin(), arr.end(), [](int& e) { std::cout << e << " "; });
    std::cout << std::endl;
    SortHeap::heap_sort(arr);
    std::for_each(arr.begin(), arr.end(), [](int& e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}




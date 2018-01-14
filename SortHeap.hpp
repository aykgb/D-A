#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace SortHeap {
/*   parent: 根节点索引
 *   tail:   最后一个叶子节点索引，结尾点
 *   自顶向下调整
 */
void adjust_max(std::vector<int>& nums, int parent, int tail) {
    int lchild = 2 * parent + 1;
    int rchild = 2 * parent + 2;
    int largest = parent;
    if(lchild <= tail && nums[lchild] > nums[largest]) {
        largest = lchild;
    }
    if(rchild <= tail && nums[rchild] > nums[largest]) {
        largest = rchild;
    }
    if(parent != largest) {
        std::swap(nums[parent], nums[largest]);
        adjust_max(nums, largest, tail);
    }
}

/*   parent: 根节点索引
 *   tail:    最后一个叶子节点索引
 */
void adjust_max1(std::vector<int>& nums, int parent, int tail) {
    while(true) {
        int lchild = parent * 2 + 1;
        int rchild = parent * 2 + 2;
        int largest = parent;
        if(lchild <= tail && nums[lchild] > nums[largest]) {
            largest = lchild;
        }
        if(rchild <= tail && nums[rchild] > nums[largest]) {
            largest = rchild;
        }
        if(largest != parent) {
            std::swap(nums[largest], nums[parent]);
            parent = largest;
        } else {
            break;
        }
    }
}

/*   parent: 根节点索引
 *   tail:    最后一个叶子节点索引
 */
void adjust_min(vector<int>& nums, int parent, int tail) {
    while(true) {
        int lchild = parent * 2 + 1;
        int rchild = parent * 2 + 2;
        int smallest = parent;
        if(lchild <= tail && nums[smallest] > nums[lchild]) {
            smallest = lchild;
        }
        if(rchild <= tail && nums[smallest] > nums[rchild]) {
            smallest = rchild;
        }
        if(smallest != parent) {
            std::swap(nums[parent], nums[smallest]);
            parent = smallest; // 向下迭代
        } else {
            break;
        }
    }
}

// 自底向上，建完堆后，只需要一次adjust即可找到最大/小元素
void build_max_heap(vector<int>& nums) {
    int len = nums.size();
    for(int i = len / 2 - 1; i > -1; i--) {
        adjust_max(nums, i, len);
    }
}

void build_min_heap(vector<int>& nums) {
    int len = nums.size();
    for(int i = len / 2 - 1; i > -1; i--) {
        adjust_min(nums, i, len);
    }
}

void heap_sort(vector<int>& nums) {
#if 1
    int tail = nums.size() - 1;
    build_max_heap(nums);
    std::swap(nums[0], nums[tail]);
    tail--;
    while(tail > 0) {
        adjust_max(nums, 0, tail);
        std::swap(nums[0], nums[tail--]);
    }
#else
    // 这种排序方式是错误的，因为取出最小堆堆顶的方式破坏了原有的堆的结构
    // 所以在数组上的堆的构建必须要有交换这一步骤
    for(size_t i = 0; i < nums.size(); i++) {
        build_min_heap(nums, i, nums.size() - 1);
    }
#endif
}

}

int test_heap_sort()
{
    vector<int> nums{-1, 3, 2, 0, -5, 6, 9, -2, 10, -29, 32, 1, 7};
    std::for_each(nums.begin(), nums.end(), [](int& e) { std::cout << e << " "; });
    std::cout << std::endl;
    SortHeap::heap_sort(nums);
    std::for_each(nums.begin(), nums.end(), [](int& e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}




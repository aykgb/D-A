#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

namespace SortMerge {

void copy(std::vector<int>& nums, int head, int tail, std::vector<int>& target) {
    int i = 0;
    while(head < tail + 1) {
        target[i++] = nums[head++];
    }
}

// merge two sorted partition of an array to whole one.
void merge(vector<int>& nums, int head, int middle, int tail) {
    int len_lpart = middle - head + 1;  // left part 包含middle索引指向的元素
    int len_rpart = tail - middle;      // right part 不包含middle索引指向的元素
    std::vector<int> lpart(len_lpart, 0);
    std::vector<int> rpart(len_rpart, 0);
    copy(nums, head, middle, lpart);
    copy(nums, middle + 1, tail, rpart);
    int i = 0, j = 0, k = head;
    while(k < tail + 1 && i < len_lpart && j < len_rpart) {
        if(lpart[i] < rpart[j]) {
            nums[k++] = lpart[i++];
        } else {
            nums[k++] = rpart[j++];
        }
    }

    while(i < len_lpart) {
        nums[k++] = lpart[i++];
    }

    while(j < len_rpart) {
        nums[k++] = rpart[j++];
    }
}

void merge_sort(std::vector<int>& nums, int head, int tail) {
    if(head < tail) { // 至少包含2个元素才能分割
        merge_sort(nums, head, (head + tail) / 2);
        merge_sort(nums, (head + tail) / 2 + 1, tail);
        merge(nums, head, (head + tail) / 2, tail);
    }
}

}

int test_merge_sort()
{
    std::vector<int> nums {0, 1, 2, 3, 4, 5, 6, 7};
    int middle  = (7 - 0) / 2;
    std::vector<int> left(middle, 0);
    std::vector<int> right(middle + 1, 0);
    std::copy_n(nums.begin(), middle, left.begin());
    std::copy_n(nums.begin() + middle, middle + 1, right.begin());

    std::for_each(left.begin(), left.end(), [](int& e){std::cout << e << " ";});
    std::cout << std::endl;
    std::for_each(right.begin(), right.end(), [](int& e){std::cout << e << " ";});
    std::cout << std::endl;

    nums = std::vector<int> { 1, 2, 8, 7, 0, -1, 12, -23, 6 };
    std::for_each(nums.begin(), nums.end(), [](int& e) { std::cout << e << " "; });
    std::cout << std::endl;
    SortMerge::merge_sort(nums, 0 , nums.size() - 1);
    std::for_each(nums.begin(), nums.end(), [](int& e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}

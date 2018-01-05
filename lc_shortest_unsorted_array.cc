#include <iostream>
#include <vector>
#include <algorithm>

extern "C" {
#include <limits.h>
}
#include <limits.h>

using namespace std;

int findUnsortedSubarray(vector<int>& nums) {
    int len = nums.size();
    if(len < 2) {
        return 0;
    }

    int left  = 0, right = len - 1;
    /* 从索引0开始从左至右找到最长升序列的最大元素索引，如 1, 4, 5, 4, ... 中的5的索引 */
    while(left < len - 1 && nums[left] <= nums[left+1]) {
        left++;
    }

    /* 从索引len - 1开始从右至左找到最长降序列的最小元素索引，如... 8,7,6,7,8 中的6的索引 */
    while(right > 0 && nums[right - 1] <= nums[right]) {
        right--;
    }

    if(left > right) return 0; // 序列是完全排序的，这直接返回0。

    /* 中间无序序列中的最大最小值 */
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = left + 1; i < right; i++) {
        if(nums[i] > max) {
            max = nums[i];
        }

        if(nums[i] < min) {
            min = nums[i];
        }
    }

    /* 找到上面找到的最长升序列中小于等于max的元素的索引 */
    while(left >= 0 && nums[left] > max) left--;
    /* 找到上面找到的最长降序列中大于等于min的元素的索引 */
    while(right < len && nums[right] < min) right++;

    return right - left - 1;
}

int main()
{
    return 0;
}


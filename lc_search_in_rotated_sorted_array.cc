#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        while(low <= high) {
            int middle = (low + high) / 2;
            if(nums[middle] < nums[low]) { // 以旋转中心为界，middle落在左半段
                if(target < nums[middle]) {
                    high = middle - 1;
                } else if(target > nums[middle]) {
                    if(target < nums[high]) {
                        low = middle + 1;
                    } else if(target > nums[high]) {
                        high = middle - 1;
                    } else {
                        return high;
                    }
                } else {
                    return middle;
                }
            } else if(nums[middle] > nums[low]) {
                if(target < nums[middle]) {
                    if(target > nums[low]) {
                        high = middle - 1;
                    } else if(target < nums[low]) {
                        low = middle + 1;
                    } else {
                        return low;
                    }
                } else if (target > nums[middle]) {
                    low = middle + 1;
                } else {
                    return middle;
                }
            } else { // nums[middle] == nums[low]
                if(target == nums[middle]) {
                    return middle;
                }

                if(target == nums[high]) {
                    return high;
                }

                break;
            }
        }

        return -1;
    }
};

int main()
{
    vector<int> nums{1, 3};
    int target = 3;

    std::cout << "target:" << target
              << " index:" << Solution().search(nums, target) << std::endl;

    return 0;
}

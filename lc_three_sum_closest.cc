#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <climits>

using namespace std;

class Solution {
public:

    // 消耗时间过长，导致超时
    int threeSumClosest(vector<int>& nums, int target) {
        vector<int> three;
        int best = nums[0] + nums[1] + nums[2];
        dfs(nums, 0, three, target, best);

        return best;
    }

    void dfs(vector<int>& nums, size_t start, vector<int>& three, int target, int& best) {
        for(size_t i = start; i < nums.size(); i++) {
            if(three.size() > 3) { // 实现剪枝动作
                continue;
            }

            three.push_back(nums[i]);

            if(three.size() == 3) {
                for(auto & e: three) {
                    std::cout << e << " ";
                }
                std::cout << std::endl;
                int sum = three[0] + three[1] + three[2];
                if(std::abs(sum - target) < std::abs(target - best)) {
                    best = sum;
                }
            }
            dfs(nums, i + 1, three, target, best);
            three.pop_back();
        }
    }

#if 0 // 错误的方法，不能够完全遍历所有可能
    // 排序、使用3个指针
    int threeSumClosest2(vector<int>& nums, int target) {
        int len = nums.size();
        if(len == 3) {
            return nums[0] + nums[1] + nums[2];
        }

        std::sort(nums.begin(), nums.end());
        int first = 0, second = 1, third = 2;
        int sum = nums[first] + nums[second] + nums[third];
        if(sum >= target) return sum;
        third++;

        int twoSum = nums[first] + nums[second];
        int preSum = sum;
        while(third < len) {
            sum = twoSum + nums[third];

            if(sum == target) return sum;
            if(sum > target) {
                if(sum - target <= target - preSum) {
                    return sum;
                } else {
                    return preSum;
                }
            }

            preSum = sum;
            sum = 0;
            third++;
        }
        third--;

        twoSum = nums[first] + nums[third];
        while(second < third) {
            sum = twoSum + nums[second];

            if(sum == target) return sum;
            if(sum > target) {
                if(sum - target <= target - preSum) {
                    return sum;
                } else {
                    return preSum;
                }
            }

            preSum = sum;
            sum = 0;
            second++;
        }
        second--;

        twoSum = nums[second] + nums[third];
        while(first < second) {
            sum = twoSum + nums[first];

            if(sum == target) return sum;
            if(sum > target) {
                if(sum - target <= target - preSum) {
                    return sum;
                } else {
                    return preSum;
                }
            }

            preSum = sum;
            sum = 0;
            first++;
        }
        first--;

        return preSum; // 最大可能的sum

    }
#endif

    // 排序、使用3个指针
    int threeSumClosest3(vector<int>& nums, int target) {
        if(nums.size() == 3) {
            return nums[0] + nums[1] + nums[2];
        }

        std::sort(nums.begin(), nums.end());
        int sum = nums[0] + nums[1] + nums[2];
        if(sum >= target) {
            return sum;
        }

        // sum < target;
        int len = nums.size();
        for(int first = 0; first < len - 2; first++){            // 固定其中一个数
            if(first > 0 && nums[first] == nums[first - 1]) {    // 跳过重复的数
                continue;
            }

            // 从剩余的数据空间中寻找2数之和
            int second = first + 1;
            int third = len - 1;
            while(second < third) {
                int thisSum = nums[first] + nums[second] + nums[third];
                if(std::abs(thisSum - target) < std::abs(sum - target)) {
                    sum = thisSum;
                    if(sum == target) {
                        return sum;
                    }
                }

                if(thisSum > target) {
                    third--;
                } else {
                    second++;
                }
            }
        }

        return sum;
    }
};

int main()
{
    std::vector<int> nums {1, 1, 1, 1};
    int target = 3;

    int res = Solution().threeSumClosest3(nums, target);

    std::cout << res << std::endl;

    return 0;
}

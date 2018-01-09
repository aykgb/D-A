#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 排序数组的2数之和，双指针法
vector<vector<int>> twoSum(vector<int>& nums, int head, int tail, int target) {
    vector<vector<int>> result;

    while(head < tail) {
        if(nums[head] > target) break; // 条件不可是>=。考虑 x0, x1, ..., 0, 0, ..., xn ,target 为0

        if(nums[head] + nums[tail] > target) {
            tail--;
        } else if(nums[head] + nums[tail] < target) {
            head++;
        } else {
            result.emplace_back(vector<int>{nums[head], nums[tail]});
            head++;
            tail--;
            while(nums[head] == nums[head-1] && nums[tail] == nums[tail+1] && head < tail) {
                head++;
                tail--;
            }
        }
    }

    return result;
}

// 1. 排序
// 2. 迭代，固定一个数，找2数之和
// 3. 可优化，迭代到大于等于和的数即可停止迭代
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    if(nums.size() < 3) return result;

    std::sort(nums.begin(), nums.end());

    for(size_t i = 0; i < nums.size() - 2; i++) {
        if(nums[i] > 0) break;

        int target = 0 - nums[i];
        if(i == 0 || nums[i] != nums[i - 1]) {
            auto res =  twoSum(nums, i + 1, nums.size() - 1, target);
            for(auto & vec : res) {
                vec.push_back(nums[i]);
                result.emplace_back(vec);
            }
        }
    }

    return result;
}

int main()
{
    // vector<int> nums {-3, -1, 0, 1, 2, -1, -4};
    // vector<int> nums {0, 0, 0, 0};
    vector<int> nums {1, 2, -2, -1};

    auto result = threeSum(nums);

    for(auto & vec : result) {
        for(auto & ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

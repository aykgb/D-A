#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 排序数组的2数之和，双指针法
vector<vector<int>> twoSum(vector<int>& arr, int head, int tail, int target) {
    vector<vector<int>> result;

    while(head < tail) {
        if(arr[head] > target) break; // 条件不可是>=。考虑 x0, x1, ..., 0, 0, ..., xn ,target 为0

        if(arr[head] + arr[tail] > target) {
            tail--;
        } else if(arr[head] + arr[tail] < target) {
            head++;
        } else {
            result.emplace_back(vector<int>{arr[head], arr[tail]});
            head++;
            tail--;
            while(arr[head] == arr[head-1] && arr[tail] == arr[tail+1] && head < tail) {
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
vector<vector<int>> threeSum(vector<int>& arr) {
    vector<vector<int>> result;
    if(arr.size() < 3) return result;

    std::sort(arr.begin(), arr.end());

    for(size_t i = 0; i < arr.size() - 2; i++) {
        if(arr[i] > 0) break;

        int target = 0 - arr[i];
        if(i == 0 || arr[i] != arr[i - 1]) {
            auto res =  twoSum(arr, i + 1, arr.size() - 1, target);
            for(auto & vec : res) {
                vec.push_back(arr[i]);
                result.emplace_back(vec);
            }
        }
    }

    return result;
}

int main()
{
    // vector<int> arr {-3, -1, 0, 1, 2, -1, -4};
    // vector<int> arr {0, 0, 0, 0};
    vector<int> arr {1, 2, -2, -1};

    auto result = threeSum(arr);

    for(auto & vec : result) {
        for(auto & ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

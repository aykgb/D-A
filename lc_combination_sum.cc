#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if(candidates.empty()) return {};
        std::sort(candidates.begin(), candidates.end());

        vector<int> ans;
        vector<vector<int>> result;
        dfs(candidates, 0, ans, result, target);

        return result;
    }

    void dfs(vector<int>& arr, int start, vector<int>& ans, vector<vector<int>>& result, int target) {
        if(target == 0) {
            result.emplace_back(ans);
            return;
        }

        for(size_t i = start; i < arr.size() && arr[i] <= target; i++) {
            ans.emplace_back(arr[i]);
            dfs(arr, i, ans, result, target - arr[i]);
            ans.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // 排序，排除特殊case
        std::sort(candidates.begin(), candidates.end());
        if(candidates[0] > target) return {};

        vector<vector<int>> result;
        find_subsets(candidates, result, target);

        return result;
    }

    int sumof(vector<int>& subset) {
        int sum = 0;
        for(auto &e: subset) {
            sum += e;
        }
        return sum;
    }

    void find_subsets(vector<int>& arr, vector<vector<int>>& result, int target) {
        // subsets的初始状态，只含有一个空集
        vector<vector<int>> subsets{{}};
        // 逐个考察nums中的元素
        for(size_t i = 0; i < arr.size() && arr[i] <= target; i++) {
            int previousN = subsets.size();
            // 逐个拿出原有subsets中的subset，放入索引i指向的元素后，再添加到subsets中。
            for(int j = 0; j < previousN; j++) {
                vector<int> subset = subsets[j];
                int count = (target - sumof(subset)) / arr[i];  // i指向的元素最多可重复次数
                for(int k = 0; k < count; k++) {
                    subset.emplace_back(arr[i]);
                    if(sumof(subset) > target) {    // 跳过，不再向下搜索，也不加入subsets中
                        break;
                    }

                    if(sumof(subset) == target) {
                        result.emplace_back(subset);
                    }

                    subsets.emplace_back(subset);
                }
            }
        }
    }
};

int main()
{
    vector<int> arr{1, 2, 3, 4, 5, 6, 7};
    int target = 7;

    auto result = Solution().combinationSum(arr, target);
    auto print_subsets = [&](){
        std::cout << "[" << std::endl;
        for(auto &subset : result) {
            std::cout << "[";
            for(auto &e : subset) {
                std::cout << e << " ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << "]" << std::endl;
    };

    print_subsets();


    return 0;
}

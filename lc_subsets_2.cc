#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<int> subset;
        set<vector<int>> subsets;

        dfs(nums, 0, subset, subsets);

        vector<vector<int>> result;
        for(auto & e : subsets) {
            result.emplace_back(e);
        }

        return result;
    }

    void dfs(vector<int>& nums, int start, vector<int>& subset, set<vector<int>>& subsets) {
        subsets.emplace(subset);
        for(size_t i = start; i < nums.size(); i++) {
            subset.emplace_back(nums[i]);
            dfs(nums, i + 1, subset, subsets);
            subset.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup2(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> subsets;
        subsets.emplace_back(vector<int>());

        for(size_t i = 0; i < nums.size();) {
            int counts = 0;
            int previousN = subsets.size();

            while(counts + i < nums.size() && nums[counts + i] == nums[i]) counts++;

            for(int j = 0; j < previousN; j++) {
                vector<int> subset = subsets[j];
                for(int k = 0; k < counts; k++) {
                    subset.emplace_back(nums[i]);
                    subsets.emplace_back(subset);
                }
            }
            i += counts;
        }

        return subsets;
    }
};

int main()
{
    vector<int> nums = {1, 2, 2, -1, 10, 8, 18, 9, 1, 2, 3, 4, 8, 8, 9, 9, 9, -10, -2, -8, -7, -6};
    auto result = Solution().subsetsWithDup2(nums);

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

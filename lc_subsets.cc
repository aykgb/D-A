#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        vector<int> sub;
        vector<vector<int>> subs;
#if 0
        subs.push_back(sub);
        dfs(arr, 0, sub, subs);
#else
        dfs1(arr, 0, sub, subs);
#endif

        return subs;
    }

    // 这个问题，每个元素都有放入或不放入2中选择，所以子集数有2^n个，这类问题称为NP问题
    // 对NP问题一般使用搜索算法，且多是深度优先搜索DFS
    // 对nums中的每个元素，都有在集合中和不在集合中2中状态，那么
    void dfs(vector<int>& arr, size_t start, vector<int>& subset, vector<vector<int>>& subsets) {
        if(start >= arr.size() ) {
            return;
        } else {
            for(size_t i = start; i < arr.size(); i++) {
                subset.push_back(arr[i]);
                subsets.push_back(subset);
                dfs(arr, i + 1, subset, subsets);
                subset.pop_back();
            }
        }
    }

    void dfs1(vector<int>& arr, size_t start, vector<int>& subset, vector<vector<int>>& subsets) {
        subsets.push_back(subset);
        for(size_t i = start; i < arr.size(); i++) {
            subset.push_back(arr[i]);
            dfs1(arr, i + 1, subset, subsets);
            subset.pop_back();
        }
    }

    vector<vector<int>> subsets2(vector<int>& arr) {
        vector<vector<int>> subsets{{}};
        for(size_t i = 0; i < arr.size(); i++) {
            int previousN = subsets.size();
            for(int j = 0; j < previousN; j++) {
                vector<int> subset = subsets[j];
                subset.emplace_back(arr[i]);
                subsets.emplace_back(subset);
            }
        }

        return subsets;
    }
};

int main()
{
    vector<int> arr {1, 2, 3};
    auto result = Solution().subsets2(arr);

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

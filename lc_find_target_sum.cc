#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // nums中都是非negative的数字，故S是最大和。
    int findTargetSumWays(vector<int>& nums, int target) {
        const int N = nums.size();
        const int S = std::accumulate(nums.begin(), nums.end(), 0);
        if(S < target) { return 0; }
        // dp[i][j] 表示前i个数和为j的方案数目
        vector<vector<int>> dp(N + 1, vector<int>(2 * S + 1, 0));
        int offset = S;
        dp[0][offset] = 1; // 前0个数和为0的可能方案数是1

        for(int i = 1; i < N + 1; i++) {
            // j = 0表示sum = -S; j = offset表示sum = 0;
            for(int j = -S; j < S + 1; j++) {
                if(j + nums[i - 1] <= S) {
                    // j + nums[i - 1]的和的方案数是
                    dp[i][j + nums[i - 1] + offset] += dp[i - 1][j + offset];
                }
                if(j - nums[i - 1] >= -S) {
                    // j - nums[i - 1]的和的方案数是
                    dp[i][j - nums[i - 1] + offset] += dp[i - 1][j + offset];
                }
            }
        }

        return dp.back()[offset + target];
    }
};

int main()
{
    vector<int> nums{1, 2, 1, 2, 1};
    int target = 3;
    int ways = Solution().findTargetSumWays(nums, target);

    std::cout << ways << std::endl;

    return 0;
}

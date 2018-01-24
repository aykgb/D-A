#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

/* 给定一个有n个正整数的数组A和一个整数sum,求选择数组A中部分数字和为sum的方案数。
当两种选取方案有一个数字的下标不一样,我们就认为是不同的组成方案。
*/

/* 单纯求方案数可用dp方法来解。*/

int main()
{
    int M = 100;
    int N = 0;
    std::cin >> M >> N;

    vector<int> arr(M, 0);
    for(int i = 0; i < M; i++) {
        arr[i] = std::rand() % 30;
    }

    /* dp[m][n] 表示取前m个元素时,找到的和为n的方案数 */
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));
    /* 取前m个元素，和为0 的case有1种方案——什么都不取 */
    for(int i = 0; i < M; i++) {
        dp[i][0] = 1;
    }
    /* 取前0个元素和为1~N的方案数为0 */
    for(int i =1; i < N + 1; i++) {
        dp[0][i] = 0;
    }

    for(int m = 1; m < M + 1; m++) {
        for(int n = 1; n < N + 1; n++) {
            /* 若不取索引为m的元素，则dp[m][n]方案数为dp[m - 1][n]. */
            if(n >= arr[m]) {
                /* 可取索引为m的元素 */
                dp[m][n] = dp[m - 1][n] + dp[m - 1][n - arr[m]];
            } else {
                dp[m][n] = dp[m - 1][n];
            }
        }
    }

    std::cout << dp[M][N] << std::endl;;

#if 1
    auto print_int = [](vector<int>& arr) {
        for(auto &e : arr) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    };

    print_int(arr);
#endif

    return 0;
}

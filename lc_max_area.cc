#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int i = 0;
        int j = n - 1;
        int res = 0;
        while(i < j) {
            res = std::max(res, std::min(height[i], height[j]) * (j - i));
            if(height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return res;
    }
};

int main()
{
    std::vector<int> nums {1, 2, 3, 0, 1, 2, 5};
    int res = Solution().maxArea(nums);
    std::cout << "max area:" << res << std::endl;

    return 0;
}

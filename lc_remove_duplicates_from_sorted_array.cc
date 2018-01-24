#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int N = nums.size();
        if(N < 2) {
            return N;
        }

        int k = 0;
        for(int i = 1; i < N; i++) {
            if(nums[i] != nums[i - 1]) {
                k++;
                if(k != i) {
                    nums[k] = nums[i];
                }
            }
        }

        int l = k;
        while(++l < N) {
            nums.erase(nums.begin() + k + 1);
        }

        return k;
    }
};

int main()
{
    std::vector<int> nums{1, 1, 1};

    Solution().removeDuplicates(nums);

    return 0;
}

#include <iostream>
#include <vector>
#include <set>

using namespace std;

void print_vector_int(vector<int>& vec) {
    for(auto & e: vec) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

class Solution {
public:
    int jump1(vector<int>& nums) {
        if(nums.size() == 1) { return 0; }
        if(nums.size() == 2) { return 1; }

        vector<int> steps{0};
        int max_value_id = 0;
        int max_value = nums[0];
        int max_reaching_id = nums[0];
        int max_reaching_id_stage = nums[0];
        for(int i = 1; i < (int)nums.size() - 1; i++) {
            int this_reaching_id = i + nums[i];
            if(this_reaching_id > max_reaching_id_stage) {
                max_reaching_id_stage = this_reaching_id;
            }

            // 这个步骤是错误的。
            if(nums[i] > max_value) {
                max_value = nums[i];
                max_value_id = i;
            }

            if(i == max_reaching_id) {
                max_reaching_id = max_reaching_id_stage;
                steps.emplace_back(max_value_id);
                max_value = 0;

                if(max_reaching_id_stage >= (int)nums.size() - 1) {
                    break;
                }
            }
        }

        print_vector_int(nums);
        print_vector_int(steps);
        return steps.size();
    }

    int jump(vector<int>& nums) {
        if(nums.size() == 1) return 0;
        if(nums.size() == 2) return 1;

        vector<int> steps{0};
        int max_value_id = 0;
        int max_reaching_id = nums[0];
        int max_reaching_id_stage = nums[0];
        for(int i = 1; i < (int)nums.size() - 1; i++) {
            int this_reaching_id = i + nums[i];
            if(this_reaching_id > max_reaching_id_stage) {
                max_reaching_id_stage = this_reaching_id;
                max_value_id = i; // 在max_reaching_id截止范围内，始终选择一个可抵达最大索引的索引。
            }

            if(i == max_reaching_id) {
                max_reaching_id = max_reaching_id_stage;
                steps.emplace_back(max_value_id);
                if(max_reaching_id_stage >= (int)nums.size() - 1) {
                     break;
                }
            }
        }

        print_vector_int(nums);
        print_vector_int(steps);
        return steps.size();
    }
};

int main()
{
    // vector<int> nums{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 7, 3, 1, 1, 1, 3, 2, 1};
    // vector<int> nums{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 7, 3, 1, 1, 3, 2, 1};
    // vector<int> nums{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 1, 1, 1};
    // vector<int> nums{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 1, 1, 7};
    vector<int> nums{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 3, 1, 2, 7, 1, 1, 1, 1, 1, 1, 1};
    // vector<int> nums{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 1, 1};
    // vector<int> nums{2, 3, 1};
    // vector<int> nums{1, 0};
    // vector<int> nums{0};
    std::cout << Solution().jump(nums) << std::endl;;

    return 0;
}

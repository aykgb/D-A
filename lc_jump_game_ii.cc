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
    int jump1(vector<int>& arr) {
        if(arr.size() == 1) { return 0; }
        if(arr.size() == 2) { return 1; }

        vector<int> steps{0};
        int max_value_id = 0;
        int max_value = arr[0];
        int max_reaching_id = arr[0];
        int max_reaching_id_stage = arr[0];
        for(int i = 1; i < (int)arr.size() - 1; i++) {
            int this_reaching_id = i + arr[i];
            if(this_reaching_id > max_reaching_id_stage) {
                max_reaching_id_stage = this_reaching_id;
            }

            // 这个步骤是错误的。
            if(arr[i] > max_value) {
                max_value = arr[i];
                max_value_id = i;
            }

            if(i == max_reaching_id) {
                max_reaching_id = max_reaching_id_stage;
                steps.emplace_back(max_value_id);
                max_value = 0;

                if(max_reaching_id_stage >= (int)arr.size() - 1) {
                    break;
                }
            }
        }

        print_vector_int(arr);
        print_vector_int(steps);
        return steps.size();
    }

    int jump(vector<int>& arr) {
        if(arr.size() == 1) return 0;
        if(arr.size() == 2) return 1;

        vector<int> steps{0};
        int max_value_id = 0;
        int max_reaching_id = arr[0];
        int max_reaching_id_stage = arr[0];
        for(int i = 1; i < (int)arr.size() - 1; i++) {
            int this_reaching_id = i + arr[i];
            if(this_reaching_id > max_reaching_id_stage) {
                max_reaching_id_stage = this_reaching_id;
                max_value_id = i; // 在max_reaching_id截止范围内，始终选择一个可抵达最大索引的索引。
            }

            if(i == max_reaching_id) {
                max_reaching_id = max_reaching_id_stage;
                steps.emplace_back(max_value_id);
                if(max_reaching_id_stage >= (int)arr.size() - 1) {
                     break;
                }
            }
        }

        print_vector_int(arr);
        print_vector_int(steps);
        return steps.size();
    }
};

int main()
{
    // vector<int> arr{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 7, 3, 1, 1, 1, 3, 2, 1};
    // vector<int> arr{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 7, 3, 1, 1, 3, 2, 1};
    // vector<int> arr{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 1, 1, 1};
    // vector<int> arr{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 1, 1, 7};
    vector<int> arr{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 3, 1, 2, 7, 1, 1, 1, 1, 1, 1, 1};
    // vector<int> arr{2, 3, 1, 1, 1, 4, 10, 1, 1, 1, 1, 1, 1, 6, 4, 5, 3, 1, 1};
    // vector<int> arr{2, 3, 1};
    // vector<int> arr{1, 0};
    // vector<int> arr{0};
    std::cout << Solution().jump(arr) << std::endl;;

    return 0;
}

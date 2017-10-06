#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, vector<int>& nums2, vector<int>& output) {
        int nums1_length = nums1.size();
        int nums2_length = nums2.size();
        int i = 0, j = 0;
        while(i < nums1_length || j < nums2_length) {
            if(i < nums1_length && j < nums2_length) {
                if(nums1[i] < nums2[j]) {
                    output.emplace_back(nums1[i++]);
                } else {
                    output.emplace_back(nums2[j++]);
                }
            } else {
                while(i < nums1_length) {
                    output.emplace_back(nums1[i++]);
                }
                while(j < nums2_length) {
                    output.emplace_back(nums2[j++]);
                }
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        std::vector<int> output;
        merge(nums1, nums2, output);
        for(auto &it : output) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
        int length = output.size();
        int median_index = length / 2;
        if(length % 2) {
            return output[median_index];
        } else {
            return ((double)output[median_index] + output[median_index - 1]) / 2;
        }
    }
};

class Solution2 {
public:
    void merge(vector<int>& nums1, vector<int>& nums2, vector<int>& output) {
        int nums1_length = nums1.size();
        int nums2_length = nums2.size();
        int i = 0, j = 0;
        while(i < nums1_length || j < nums2_length) {
            if(i < nums1_length && j < nums2_length) {
                if(nums1[i] < nums2[j]) {
                    output.emplace_back(nums1[i++]);
                } else {
                    output.emplace_back(nums2[j++]);
                }
            } else {
                while(i < nums1_length) {
                    output.emplace_back(nums1[i++]);
                }
                while(j < nums2_length) {
                    output.emplace_back(nums2[j++]);
                }
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty() && !nums2.empty()) {
            return nums2.size() % 2 ? nums2[nums2.size() / 2] : (double(nums2[nums2.size() / 2]) + nums2[nums2.size() / 2 - 1]);
        }
        if(!nums1.empty() && nums2.empty()) {
            return nums1.size() % 2 ? nums1[nums1.size() / 2] : (double(nums1[nums1.size() / 2]) + nums1[nums1.size() / 2 - 1]);
        }
        if(nums1.empty() && nums2.empty()) {
            return 0;
        }
        if(nums1.size() < nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int total_length = nums1.size() + nums2.size();
        /*Find the suitable i' j' and so that:
        *   if length is odd then the median must be ether nums1[i'] or nums2[j'],
        *   otherwise the median is (x + y) / 2:
        *   case a: both of {x, y} are contained on nums1, and median = (nums1[i'] + nums2[i' + 1]) / 2;
        *   case b: both of {x, y} are contained on nums2, and median = (nums2[j'] + nums2[j' + 1]) / 2;
        *   case c: x = (nums1[i'] + nums2[j']) / 2;
        */
        size_t i = 0, j = 0;
        while(i < nums1.size()) {
            if(j < nums2.size()) {
                if(nums1[i] <= nums2[j]) {
                    i++;
                } else {
                    j++;
                }
            } else {
                i++;
            }
            int visited_length = i + j + 2;

            if(visited_length > total_length / 2) {
                break;
            }
        }

        if(i == nums1.size()) {
            i--;
        }
        if(j == nums2.size()) {
            j--;
        }

        if(total_length % 2) {
            if(nums1[i] <= nums2[j]) {
                return nums1[i];
            } else {
                return nums2[j];
            }
        } else {
            return ((double)nums1[i] + nums2[j]) / 2;
        }
    }
};


void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> nums1 = stringToIntegerVector(line);
        getline(cin, line);
        vector<int> nums2 = stringToIntegerVector(line);

        double ret = Solution().findMedianSortedArrays(nums1, nums2);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}

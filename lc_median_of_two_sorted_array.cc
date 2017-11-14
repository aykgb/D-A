#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

/* time: O(n) space: O(n)*/
class Solution {
public:
    void merge(vector<int>& A, vector<int>& B, vector<int>& C) {
        int lenA = A.size();
        int lenB = B.size();
        int i = 0, j = 0;
        while(i < lenA || j < lenB) {
            if(i < lenA && j < lenB) {
                if(A[i] < B[j]) {
                    C.emplace_back(A[i++]);
                } else {
                    C.emplace_back(B[j++]);
                }
            } else {
                while(i < lenA) {
                    C.emplace_back(A[i++]);
                }
                while(j < lenB) {
                    C.emplace_back(B[j++]);
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

/* time: O(n) space: O(1)*/
class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        if(A.size() < B.size()) {
            return findMedianSortedArrays(B, A);
        }

        int lenA = A.size();
        int lenB = B.size();
        int total_length = lenA + lenB;
        /*Find the suitable i' j' and so that:
        *   if length is odd then the median must be ether nums1[i'] or nums2[j'],
        *   otherwise the median is (x + y) / 2:
        *   case a: both of {x, y} are contained on nums1, and median = (nums1[i'] + nums2[i' + 1]) / 2;
        *   case b: both of {x, y} are contained on nums2, and median = (nums2[j'] + nums2[j' + 1]) / 2;
        *   case c: x = (nums1[i'] + nums2[j']) / 2;
        */
        int i = 0, j = 0;
        while(i < lenA) {
            if(j < lenB) {
                if(A[i] <= B[j]) {
                    i++;
                } else {
                    j++;
                }
            } else {
                i++;
            }

            if((i + j) > total_length / 2) {
                break;
            }
        }

        std::cout << i << " " << j << std::endl;

        if(lenA == 0) { // means that both of nums1 and nums2 are empty.
            return 0;
        }

        if(lenB == 0) { // only nums2 is empty.
            if(lenA % 2) {
                return A[lenA / 2]; // odd
            } else {
                return (double(A[lenA / 2]) + A[lenA / 2 - 1]) / 2; // even
            }
        }

        /*some other cases.*/

        return 0;
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

        double ret = Solution2().findMedianSortedArrays(nums1, nums2);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}

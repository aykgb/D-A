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
    /* 2个排序数组的中位数要么在A中，要么在B中.*/
    int findKthOfTwoSortedArrays(vector<int>& A, int Ahead, int Atail, vector<int>& B, int Bhead, int Btail, int k) {
        if(Ahead > Atail) return B[Bhead + k - 1]; // 这种情况说明Kth不在A中
        if(Bhead > Btail) return A[Ahead + k - 1]; // 这种情况说明Kth不在B中

        int Amid = (Ahead + Atail) / 2;
        int Bmid = (Bhead + Btail) / 2;

        if(A[Amid] <= B[Bmid]) {
            if(k <= (Amid - Ahead) + (Bmid - Bhead) + 1) {  // kth 的数值肯定小于B[Bmid]
                return findKthOfTwoSortedArrays(A, Ahead, Atail, B, Bhead, Bmid - 1, k);
            } else {                                        // kth 的数值肯定大于A[Amid]
                return findKthOfTwoSortedArrays(A, Amid + 1, Atail, B, Bhead, Btail, k - (Amid - Ahead + 1));
            }
        } else { // B[Amid] < A[Bmid];
            if(k <= (Amid - Ahead) + (Bmid - Bhead) + 1) {
                return findKthOfTwoSortedArrays(A, Ahead, Amid - 1, B, Bhead, Btail, k);
            } else {
                return findKthOfTwoSortedArrays(A, Ahead, Atail, B, Bmid + 1, Btail, k - (Bmid - Bhead + 1));
            }
        }
     }

    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        int Alen = A.size();
        int Blen = B.size();

        int k = (Alen + Blen) / 2 + 1;
        int v = findKthOfTwoSortedArrays(A, 0, Alen - 1, B, 0, Blen - 1, k);
        if((Alen + Blen) % 2) {
            return v;
        } else {
            int v1 = findKthOfTwoSortedArrays(A, 0, Alen - 1, B, 0, Blen - 1, k - 1);
            return double(v + v1)/ 2;
        }
    }
};

int main() {
    std::vector<int> nums1 {1, 2};
    std::vector<int> nums2 {3, 4};

    double ret = Solution2().findMedianSortedArrays(nums1, nums2);

    std::cout << ret << std::endl;

    return 0;
}

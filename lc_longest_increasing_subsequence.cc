#include <iostream>
#include <vector>

using namespace std;

int longestIncreasingSubsequence_DP(const std::vector<int>& A) {
    int res = 0;
    int lenA = A.size();
    std::vector<int> lis(lenA, 1);
    for(int i = 0; i < lenA; i++) {
        for(int j = 0; j < i; j++) {
            if(A[i] > A[j]) {
                lis[i] = std::max(lis[i], lis[j] + 1);
            }
        }

        res = std::max(lis[i], res);
    }

    return res;
}

int longestIncreasingSubsequence(const std::vector<int>& A) {
    std::vector<int> ends(A[0]);
    for(auto & item : A) {
        if(item < ends[0]) ends[0] = item;
        else if(item > ends.back()) ends.push_back(item);
        else {
            int left = 0, right = ends.size();
            while(left < right) {
                int mid = left + (right - left) / 2;
                if(ends[mid] < item) left = mid + 1;
                else right = mid;
            }
            ends[right] = item;
        }
    }

    return ends.size();
}

int main()
{
    std::vector<int> A {0, 2, 1, 4, 6, 7, 3, 9, 5};

    int len = longestIncreasingSubsequence(A);

    std::cout << len << std::endl;

    return 0;
}

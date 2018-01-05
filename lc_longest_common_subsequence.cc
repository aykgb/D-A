#include <iostream>
#include <vector>

using namespace std;

//
int longestCommonSubsequence(const string& A, const string& B) {
    if(A.empty()) return 0;
    if(B.empty()) return 0;

    int lenA = A.size();
    int lenB = B.size();
    vector<vector<int>> lcs = \
        vector<vector<int>>(lenA + 1, vector<int>(lenB + 1, 0));

    for(int i = 1; i < lenA + 1; i++) {
        for(int j = 1; j < lenB + 1; j++) {
            if(A[i - 1] == B[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    return lcs[lenA][lenB];
}

int main()
{
    string A = "abcdef";
    string B = "fedabg";

    int len = longestCommonSubsequence(A, B);

    std::cout << len << std::endl;;
}

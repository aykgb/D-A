#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& arr) {
        int N = arr.size();
        if(N < 2) {
            return N;
        }

        int k = 0;
        for(int i = 1; i < N; i++) {
            if(arr[i] != arr[i - 1]) {
                k++;
                if(k != i) {
                    arr[k] = arr[i];
                }
            }
        }

        int l = k;
        while(++l < N) {
            arr.erase(arr.begin() + k + 1);
        }

        return k;
    }
};

int main()
{
    std::vector<int> arr{1, 1, 1};

    Solution().removeDuplicates(arr);

    return 0;
}

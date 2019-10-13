#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& arr, int target) {
        int low = 0;
        int high = arr.size() - 1;
        while(low <= high) {
            int middle = (low + high) / 2;
            if(arr[middle] < arr[low]) { // 以旋转中心为界，middle落在左半段
                if(target < arr[middle]) {
                    high = middle - 1;
                } else if(target > arr[middle]) {
                    if(target < arr[high]) {
                        low = middle + 1;
                    } else if(target > arr[high]) {
                        high = middle - 1;
                    } else {
                        return high;
                    }
                } else {
                    return middle;
                }
            } else if(arr[middle] > arr[low]) {
                if(target < arr[middle]) {
                    if(target > arr[low]) {
                        high = middle - 1;
                    } else if(target < arr[low]) {
                        low = middle + 1;
                    } else {
                        return low;
                    }
                } else if (target > arr[middle]) {
                    low = middle + 1;
                } else {
                    return middle;
                }
            } else { // arr[middle] == arr[low]
                if(target == arr[middle]) {
                    return middle;
                }

                if(target == arr[high]) {
                    return high;
                }

                break;
            }
        }

        return -1;
    }
};

int main()
{
    vector<int> arr{1, 3};
    int target = 3;

    std::cout << "target:" << target
              << " index:" << Solution().search(arr, target) << std::endl;

    return 0;
}

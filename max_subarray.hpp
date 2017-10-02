#ifndef __MAX_SUBARRAY_HPP_
#define __MAX_SUBARRAY_HPP_

#include <vector>
#include <tuple>
#include "utils.hpp"

using namespace std;

const int INT_MIN= 0x80000000;
const int INT_MAX= 0x7fffffff;


/* i, j indicates the range of subarray which is continuous.
 *  return tuple {low-bound, high-bound, max-sum}
 */
std::tuple<int, int, int> find_max_subarray(int *A, int length)
{
    int max_sum = INT_MIN, sum = 0, low= 0, high = 0;
    for(int i = 0; i < length; ++i) {
        for(int j = i; j < length; ++j) {
            sum = 0;
            for(int k = i; k <= j; k++) {
                sum += A[k];
                if(sum > max_sum) {
                    max_sum = sum;
                    low = i;
                    high = j;
                }
            }
        }
    }

    return std::make_tuple(low, high, max_sum);
}

std::tuple<int, int, int> find_max_subarray2(int *A, int length) {
    int max_sum = INT_MIN, sum = 0, low = 0, high= 0;
    for(int i = 0; i < length; i++) {
        sum = 0;
        for(int j = i; j < length; j++) {
            sum += A[j];
            if(sum > max_sum) {
                max_sum = sum;
                low = i;
                high = j;
            }
        }
    }

    return std::make_tuple(low, high, max_sum);
}

std::tuple<int, int, int> find_max_crossing_subarray(int *A, int low, int mid, int high) {
    int sum_left = INT_MIN, sum_right = INT_MIN;
    int max_left = 0, max_right = 0;
    int sum = 0;
    for(int i = mid; i >= low; i--) {
        sum += A[i];
        if(sum > sum_left) {
            sum_left = sum;
            max_left = i;
        }
    }
    sum = 0;
    for(int i = mid + 1; i <= high; i++) {
        sum += A[i];
        if(sum > sum_right) {
            sum_right = sum;
            max_right = i;
        }
    }

    return std::make_tuple(max_left, max_right, sum_left + sum_right);
}

std::tuple<int, int, int> find_max_subarray3(int *A, int low, int high) {
    /* basic case.*/
    if(low == high) {
        return std::make_tuple(low, high, A[low]);
    }

    /* recursive resolve.*/
    int mid = (low + high) / 2;
    auto left_result = find_max_subarray3(A, low, mid);
    auto right_result = find_max_subarray3(A, mid + 1, high);

    /* assemble procedure. */
    auto crossing_result = find_max_crossing_subarray(A, low, mid, high);
    int left_sum = std::get<2>(left_result);
    int right_sum = std::get<2>(right_result);
    int crossing_sum = std::get<2>(crossing_result);
    if(left_sum >= right_sum && left_sum >= crossing_sum) {
        return left_result;
    } else if (right_sum >= left_sum && right_sum >= crossing_sum) {
        return right_result;
    } else {
        return crossing_result;
    }
}

std::tuple<int, int, int> find_max_subarray4(int *A, int length) {
    int max_sum = A[0], sum = 0;
    int low = 0, high = 0, low_tmp = 0;
    for(int i = 0; i < length; i++) {
        sum += A[i];
        if(sum < 0) {
            low_tmp = i;
        }
        if(sum > max_sum) {
            max_sum = sum;
            low = low_tmp;
            high = i;
        }
    }

    return std::make_tuple(low, high, max_sum);
}

void tst_find_max_subarray() {
    // int A[] = {-1, -2, -3, -4, -6, -9, -8, -2, -2, -10, -5};
    // int A[] = {1, 2, 3, 4, 6, 9, 8, 2, 2, 10, 5};

    int A[] = {1, 2, -3, 4, 6, -9, 8, 2, -2, 10, -5};
    // auto result = find_max_subarray4(A, 11);
    auto result = find_max_subarray3(A, 0, 10);

    int low = std::get<0>(result);
    int high = std::get<1>(result);
    int max_sum = std::get<2>(result);

    print(A, 11);
    print(A + low, high - low + 1);
    std::cout << "max_sum: " << max_sum << std::endl;
}

#endif

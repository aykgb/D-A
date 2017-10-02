#ifndef __MAX_SUBARRAY_HPP_
#define __MAX_SUBARRAY_HPP_

#include <vector>
#include <tuple>

using namespace std;


/* i, j indicates the range of subarray which is continuous.
 *  return tuple {low-bound, high-bound, max-sum}
 */
std::tuple<int, int, int> max_sub_array(int *A, int length)
{
    int max_sum = 0, sum = 0, low= 0, high = 0;
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

std::tuple<int, int, int> max_sub_array2(int *A, int length) {
    int max_sum = 0, sum = 0, low = 0, high= 0;
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

    return std::make_tuple(low, high, sum);
}

std::tuple<int, int, int> find_max_crossing_subarray(int *A, int length) {

}

#endif

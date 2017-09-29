#ifndef _BINARY_SEARCH_HPP_
#define _BINARY_SEARCH_HPP_

#include <iostream>
#include "sort_simple.hpp"
#include "utils.hpp"

int binary_search(int *A, int length, int target) {
    int low = 0;
    int high = length - 1;

    while(high >= low) {
        int middle = low + high;
        if(A[middle] == target) {
            return middle;
        } else if (target > A[middle]) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return -1;
}

int main()
{
    int A[] = {5, 12, 3, 44, 2, 33, 89, 1, 0, 9, 56, 23};
    insert_sort(A, 12);
    print(A, 12);

    int pos = binary_search(A, 12, 44);

    std::cout << "pos: " << pos << std::endl;

    return 0;
}

#endif

#ifndef _SIMPLE_SORT_HPP_
#define _SIMPLE_SORT_HPP_

#include "config.hpp"

void selection_sort(int* A, int length) {
    for(int i = 0; i < length; i++) {
        int loc_min = i;
        for(int j = i; j < length; j++) {
            if(A[loc_min] > A[j]) {
                loc_min = j;
            }
        }

        std::swap(A[loc_min], A[i]);
    }
}

void buble_sort(int* A, int length) {
    for(int i = 0; i < length; i++) {
        for(int j = length - 1; j > i; j--) {
            if(A[j] < A[i]) {
                std::swap(A[j], A[i]);
            }
        }
    }
}

#endif

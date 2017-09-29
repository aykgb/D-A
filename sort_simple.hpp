#ifndef _SIMPLE_SORT_HPP_
#define _SIMPLE_SORT_HPP_

#include "config.hpp"

void buble_sort(int* A, int length) {
    for(int i = 0; i < length; i++) {
        for(int j = length - 1; j > i; j--) {
            if(A[j] < A[i]) {
                std::swap(A[j], A[i]);
            }
        }
    }
}

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

void insert_sort(int* A, int length) {
    for(int i = 1; i < length; i++) {
        int key = A[i];
        int j = i - 1;
        while(j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }

        A[j + 1] = key;
    }
}

#endif

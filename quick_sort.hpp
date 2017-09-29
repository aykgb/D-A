#ifndef _QUICK_SORT_HPP_
#define _QUICK_SORT_HPP_

#include "config.hpp"

int partition(int *A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    int j = p;
    for(; j < r; j++) {
        if(A[j] <= x) {
            i++;
            if(i != j) {
                std::swap(A[i], A[j]);
            }
        }
    }
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

void quick_sort(int *A, int p, int r) {
    if(p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

#endif

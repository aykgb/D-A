#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_

#include "config.hpp"

/* Merge two ordered array. */
void merge(int* A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1 + 1];
    int R[n2 + 1];
    L[n1] = 99999;
    R[n2] = 99999;
    memmove(L, A + p, (n1 * sizeof(int)));
    memmove(R, A + q + 1, (n2 * sizeof(int)));

    int i = 0, j = 0;
    for(int k = p; k <= r; k++) {
        if(L[i] < R[j]) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
}

void merge_sort(int* A, int p, int r) {
    if(p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
        // print(A, r - p + 1);
    }
}

#endif

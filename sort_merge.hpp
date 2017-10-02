#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_

#include "utils.hpp"

/* Merge two ordered array. */
void merge(int* A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1 + 1], R[n2 + 1];
    L[n1] = 99999;
    R[n2] = 99999; // 使用哨兵
    memmove(L, A + p, (n1 * sizeof(int)));
    memmove(R, A + q + 1, (n2 * sizeof(int)));

    int i = 0, j = 0;
    for(int k = p; k <= r; k++) {
        if(L[i] <= R[j]) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
}

void merge2(int *A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], R[n2];
    memmove(L, A + p, n1 * sizeof(int));
    memmove(R, A + q + 1, n2 * sizeof(int));

    int i = 0, j = 0, k = p;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }

    while(i < n1) {
        A[k++] = L[i++];
    }

    // while(j < n2) {
    //     A[k++] = R[j++];
    // }

    /* Will cause that the last element of the longer array(between L and R) do not
     * put into right place of A.*/
    // while(i < n1 && j < n2) {
    //     if(L[i] <= R[j]) {
    //         if(i < n1) A[k++] = L[i++];
    //     } else {
    //         if(j < n2) A[k++] = R[j++];
    //     }
    //     // print(A, 15);
    // }
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

void tst_merge() {
    int A[] = {1, 6, 7, 9, 20, 31, 2, 3, 5, 11, 12, 15, 17, 21, 23};
    // merge(A, 0, 5, 14);
    merge2(A, 0, 5, 14);
    print(A, 15);
}
#endif

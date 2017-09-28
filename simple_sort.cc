#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>

#include <string.h>

const size_t LENGTH = 20;

using namespace std;

void print(int *A, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << std::setw(5) << A[i];
        if ((i + 1) % 20 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

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

int main()
{
    int A[100];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    for(size_t i = 0; i < LENGTH ; i++) {
        A[i] = dis(gen);
    }

    // merge_sort(A, 0, LENGTH - 1);
    selection_sort(A, LENGTH);
    print(A, LENGTH);
}

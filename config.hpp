#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

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

#endif

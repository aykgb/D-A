#include <iostream>
#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <sstream>
#include <chrono>

#include "SortQuick.hpp"
#include "SortSimple.hpp"

int main(int argc, char *argv[])
{
    (void)argv;
    bool test_perf = false;
    if(argc > 1) {
        test_perf = true;
    }

    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<> dist{0, 30}; // 正态分布，平均数为0，标准差为100

    int arr_len = 20;
    if(test_perf) arr_len = 5000;

    std::vector<int> vec;
    for(int i = 0; i < arr_len; i++) {
        vec.push_back(std::round(dist(gen)));
        // vec.push_back(i * 2);
    }

    auto print_vector = [&]() {
        if(!test_perf) {
            for(auto & e: vec) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }
    };
    (void)print_vector;

    auto begin = std::chrono::steady_clock::now();
    print_vector();
    // SortQuick::quick_sort(vec, 0, vec.size() - 1);
    // SortSimple::bubble_sort(vec);
    // SortSimple::bubble_sort2(vec);
    // SortSimple::bubble_sort3(vec);
    // SortSimple::insert_sort(vec);
    // SortSimple::insert_sort2(vec);
    SortSimple::select_sort(vec);
    print_vector();
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - begin;
    std::cout << elapsed.count() << std::endl;

    return 0;
}

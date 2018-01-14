#include <iostream>
#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <set>

#include "SortSimple.hpp"
#include "SortQuick.hpp"
#include "SortMerge.hpp"
#include "SortHeap.hpp"

#if 0
#include "boost/variant.hpp"
using sort_method_type_i = std::function<void(std::vector<int>&)>;
using sort_method_type_ii = std::function<void(std::vector<int>&, int, int)>;

using VariantSort = boost::variant<
                           sort_method_type_i,
                           sort_method_type_ii>;

class MyVisitor : public boost::static_visitor<void> {
public:
    void operator()(sort_method_type_i sort_func) {
        (void)sort_func;
    }

    void operator()(sort_method_type_ii sort_func){
        (void)sort_func;
    }
};

std::unordered_map<std::string, VariantSort> sort_methods {
    { "bubble", { SortSimple::bubble_sort } },
    { "select", { SortSimple::select_sort } },
    { "insert", { SortSimple::insert_sort } },
    { "quick", { SortQuick::quick_sort } },
    { "merge", { SortMerge::merge_sort } }
};

void test(const std::string& sort_type) {
    VariantSort sort_method_v = sort_methods[sort_type];
}
#endif

std::set<std::string> sort_type {
    "bubble",
    "select",
    "insert",
    "quick",
    "merge",
    "heap"
};

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "Input two parameters at least, must specify sort type." << std::endl;
        return -1;
    }
    std::string type  = argv[1];
    if(sort_type.find(type) == sort_type.end()) {
        std::cout << "using default bubble sort type." << std::endl;
        type = "bubble";
    } else {
        std::cout << "using " << type << " sort type." << std::endl;
    }

    double range = 30;
    bool test_perf = false;
    if(argc > 2) {
        test_perf = true;
        range = 100000;
    }

    std::random_device rd{};
    std::mt19937 gen(rd());
    std::normal_distribution<> dist{0, range}; // 正态分布，平均数为0，标准差为100

    int arr_len = 20;
    if(test_perf) {
        if(argc > 3) {
            arr_len= atoi(argv[3]);
        } else {
            arr_len = 10000;
        }
    }

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

    std::cout << "start sorting..." << std::endl;
    auto begin = std::chrono::steady_clock::now();
    print_vector();
    if(type == "bubble") {
        SortSimple::bubble_sort(vec);
    } else if(type == "select") {
        SortSimple::select_sort(vec);
    } else if(type == "insert") {
        SortSimple::insert_sort(vec);
    } else if(type == "quick") {
        SortQuick::quick_sort(vec, 0, vec.size() - 1);
    } else if(type == "merge") {
        SortMerge::merge_sort(vec, 0, vec.size() - 1);
    } else if(type == "heap") {
        SortHeap::heap_sort(vec);
    } else {

    }
    // SortSimple::bubble_sort(vec);
    // SortSimple::bubble_sort2(vec);
    // SortSimple::bubble_sort3(vec);
    // SortSimple::insert_sort(vec);
    // SortSimple::insert_sort2(vec);
    // SortSimple::select_sort(vec);

    // int p = SortQuick::partition1(vec, 0, vec.size() - 1);
    // std::cout << "partition index: " << p << std::endl;

    // SortQuick::quick_sort(vec, 0, vec.size() - 1);
    print_vector();
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - begin;
    std::cout << elapsed.count() << std::endl;

    return 0;
}

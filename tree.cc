#include <iostream>
#include <vector>

#include "binary_tree.hpp"

using namespace std;

int main()
{
    std::vector<int> rec { 2, 3, 1, 5, 7, 9, 8, 3, 2, 10, 11, 23 };
    std::vector<int> aft;
    BiTNode *tree = nullptr;
    create_tree2(tree, rec);
    traverse_preorder(tree, aft);
    for(auto &item: aft) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // std::cout << tree->data << std::endl;

    return 0;
}

cmake_minimum_required(VERSION 2.8.2)
project(dsaago)

add_definitions(-g -O0 -Wall --std=c++11)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(base_binary_tree base_binary_tree.cc)

# link_libraries(base_binary_list) # 全局的链接一个库，对任何可执行文件的编译都会链接该库
add_executable(base_big_number base_big_number.cc)
add_executable(base_quick_sort base_quick_sort.cc)
add_executable(base_heap_sort base_heap_sort.cc)
add_executable(base_merge_sort base_merge_sort.cc)
add_executable(base_binary_tree_print base_binary_tree_print.cc)

add_executable(lc_bintree_level_order_traversal lc_bintree_level_order_traversal.cc)
target_link_libraries(lc_bintree_level_order_traversal base_binary_tree)

add_executable(lc_bintree_zigzag_level_order_traversal lc_bintree_zigzag_level_order_traversal.cc)
target_link_libraries(lc_bintree_zigzag_level_order_traversal base_binary_tree)


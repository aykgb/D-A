cmake_minimum_required(VERSION 2.8.9)
project(ds)

add_definitions(
    --std=c++11
    -g -O0
    -W -Wall
    )

include_directories(${PROJECT_SOURCE_DIR})

link_directories(
    /usr/lib
    /usr/local/lib
    )

link_libraries(
    pthread
    boost_regex
    boost_thread
    boost_system
    )

add_executable(lc_longest_palindrome lc_longest_palindrome.cc)
add_executable(lc_longest_substring lc_longest_substring.cc)
add_executable(lc_median_of_two_sorted_array lc_median_of_two_sorted_array.cc)
add_executable(lc_reverse_int lc_reverse_int.cc)
add_executable(lc_two_sum lc_two_sum.cc)

cmake_minimum_required(VERSION 3.17)
project(week2 C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_BUILD_TYPE Debug)

add_executable(huiwenshu huiwenshu.c)
add_executable(merge_polynomial merge_polynomial.c)
add_executable(test test.c)
add_executable(sort sort.c)
cmake_minimum_required(VERSION 3.9)
project(Contest12)

set(CMAKE_CXX_STANDARD 11)

add_executable(task1 task1-places.cpp)
add_executable(task2 task2-AStar.cpp)
add_executable(task3 task3-sieve-of-Eratosthenes.cpp)
add_executable(testThis test.cpp)

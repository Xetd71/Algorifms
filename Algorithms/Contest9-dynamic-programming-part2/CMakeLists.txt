cmake_minimum_required(VERSION 3.9)
project(Contest9)

set(CMAKE_CXX_STANDARD 11)

add_executable(task1
        task1-stones/task1-stones.cpp
        task1-stones/ReadWriter.h
)

add_executable(task2
        task2-knapsack/task2-knapsack.cpp
        task2-knapsack/ReadWriter.h
)

add_executable(task3
        task3-greedy-knapsack/task3-greedy-knapsack.cpp
        task3-greedy-knapsack/ReadWriter.h
)

add_executable(task4
        task4-knight/task4-knight.cpp
        task4-knight/ReadWriter.h
)

add_executable(TestThis test.cpp)

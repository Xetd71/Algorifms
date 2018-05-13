cmake_minimum_required(VERSION 3.9)
project(Contest10)

set(CMAKE_CXX_STANDARD 11)

set(SUCK_LIB bigInt/BigIntegerAlgorithms.hh)

add_executable(task1 task1.cpp ${SUCK_LIB})
add_executable(task2 task2.cpp ${SUCK_LIB})
add_executable(task3 task3.cpp ${SUCK_LIB})
add_executable(task4 task4.cpp ${SUCK_LIB})

cmake_minimum_required(VERSION 3.9)
project(Contest16_minimal_spanning_tree)

set(CMAKE_CXX_STANDARD 11)

add_executable(task1
        task1-boruvka-algorithm/Edge.h
        task1-boruvka-algorithm/main.cpp
        task1-boruvka-algorithm/ReadWriter.h)

add_executable(task2
        task2-prim-algorithm/Edge.h
        task2-prim-algorithm/main.cpp
        task2-prim-algorithm/ReadWriter.h)

add_executable(task3
        task3-kruskal-algorithm/Edge.h
        task3-kruskal-algorithm/main.cpp
        task3-kruskal-algorithm/ReadWriter.h)


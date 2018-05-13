cmake_minimum_required(VERSION 3.9)
project(Contest13_dancing_links_algorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(task1 task1-matrix-for-dancing-links/ReadWriter.h task1-matrix-for-dancing-links/task1-matrix-for-dancing-links.cpp)
add_executable(task2 task2-dancing-links-algo/task2-dancing-links-algo.cpp task2-dancing-links-algo/ReadWriter.h)
add_executable(task3 task3-first-counter-task/task3-first-counter-task.cpp task3-first-counter-task/ReadWriter.h)

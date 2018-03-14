cmake_minimum_required(VERSION 3.8)
project(SpellCheking)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/dictionary.h
        src/hashset.cpp
        src/hashset.h
        src/main.cpp)

add_executable(SpellCheking ${SOURCE_FILES})
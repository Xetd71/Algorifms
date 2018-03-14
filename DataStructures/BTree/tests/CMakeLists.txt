project(BTreeTests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

add_executable(BTreeTests
        ../src/btree.cpp
        ../src/btree.h
        ../src/btree_adapters.h
        ../src/utils.h
        adapters1_tests.cpp
        btree1_tests.cpp
        individual.h
        btree_student_test_NotMine.cpp
        btree_student_tests.cpp
)

target_link_libraries(BTreeTests gtest gtest_main)

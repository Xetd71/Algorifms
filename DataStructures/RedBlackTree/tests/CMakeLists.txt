project(RedBlackTree_tests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

set(SOURCE_FILES
        individual.h
        def_dumper.h
        rbtree_prv1_test.cpp
        rbtree_pub1_test.cpp
        ../src/rbtree.h
        ../src/rbtree.hpp
        )

add_executable(RedBlackTree_tests ${SOURCE_FILES})

target_link_libraries(RedBlackTree_tests gtest gtest_main)

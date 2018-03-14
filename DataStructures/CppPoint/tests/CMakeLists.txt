project(CppPoint_tests)

add_subdirectory(../../googletest googletest)

include_directories(../../googletest/googletest/include)

add_executable(CppPoint_tests
        ../src/xipoint.cpp
        ../src/xipoint.h
        point_array_test.cpp
        point_test.cpp
)

target_link_libraries(CppPoint_tests gtest gtest_main)

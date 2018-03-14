Project(SafeArrayTests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

add_executable(SafeArrayTests
    safearray_test.cpp
    subject_test.cpp
    ../src/safearray.h
    ../src/safearray.hpp
    ../src/subject.h
    ../src/subject.cpp
)


target_link_libraries(SafeArrayTests gtest gtest_main)

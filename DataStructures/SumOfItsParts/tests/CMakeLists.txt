project(SumOfItsPartsTests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

set(SOURCE_FILES
        Part_Student_Tests.cpp
        NameContainer_Student_Tests.cpp
        ../src/parts.h
        ../src/parts.cpp
)

add_executable(SumOfItsPartsTests ${SOURCE_FILES})
target_link_libraries(SumOfItsPartsTests gtest gtest_main)

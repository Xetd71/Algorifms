project(CyberPoliceTests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

add_executable(CyberPoliceTests SkipList_Student_Tests.cpp)

target_link_libraries(CyberPoliceTests gtest gtest_main)

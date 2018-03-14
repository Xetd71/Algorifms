project(StackQueueTests)

add_subdirectory(../../googletest googletest)

include_directories(../../googletest/googletest/include)

add_executable(StackQueueTests
        NiceStackTests.cpp
        Misha_Tests.cpp
        NiceQueueTests.cpp
)

target_link_libraries(StackQueueTests gtest gtest_main)

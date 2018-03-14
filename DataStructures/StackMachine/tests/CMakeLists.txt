Project(StackMachineTests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

add_executable(StackMachineTests
    int_stack_test.cpp
    stack_machine_test.cpp
    ../src/int_stack.cpp
    ../src/int_stack.h
    ../src/stack_machine.cpp
    ../src/stack_machine.h
)

target_link_libraries(StackMachineTests gtest gtest_main)

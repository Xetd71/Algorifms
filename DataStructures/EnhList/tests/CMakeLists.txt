project(EnhListTests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

add_executable(EnhListTests
        ../src/bidi_linked_list.h
        ../src/bidi_linked_list.hpp
        bidi_linked_list_test.cpp
        BidiLinkedList_Student_Test.cpp
        BidiLinkedList_Stas_Test.cpp
        BidiLinkedListIterator_Student_Test.cpp)

target_link_libraries(EnhListTests gtest gtest_main)

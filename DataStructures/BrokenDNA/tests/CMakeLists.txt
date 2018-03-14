project(BrokenDNATests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

add_executable(BrokenDNATests
        ../src/dna_element.cpp
        ../src/dna_element.h
        ../src/dna_repairer.cpp
        ../src/dna_repairer.h
        ../src/linked_list.h
        ../src/linked_list.hpp
        LinkedList_tests.cpp
        Mish_LinkedList.cpp
        Misha_DNAElement.cpp
)

target_link_libraries(BrokenDNATests gtest gtest_main)

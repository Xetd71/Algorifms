project(KDZ1Tests)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

add_executable(KDZ1Tests
        ../../src/FileEncoder.h


        ../../src/TableEncoders/TableEncoder.h
        ../../src/TableEncoders/TableEncoder.cpp

        ../../src/TableEncoders/Huffman/HuffmanEncoder.h
        ../../src/TableEncoders/Huffman/HuffmanEncoder.cpp
        HuffmanTests.cpp

        ../../src/TableEncoders/Fano/FanoEncoder.h
        ../../src/TableEncoders/Fano/FanoEncoder.cpp
        FanoTests.cpp


        ../../src/LZ77/LZ77Encoder.h
        ../../src/LZ77/LZ77Encoder.cpp
        LZ77Tests.cpp
)

target_link_libraries(KDZ1Tests gtest gtest_main)

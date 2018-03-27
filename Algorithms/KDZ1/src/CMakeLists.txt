project(KDZ1)

add_library(KDZ1
        FileEncoder.h

        TableEncoders/TableEncoder.h
        TableEncoders/TableEncoder.cpp

        TableEncoders/Huffman/HuffmanEncoder.h
        TableEncoders/Huffman/HuffmanEncoder.cpp

        TableEncoders/Fano/FanoEncoder.h
        TableEncoders/Fano/FanoEncoder.cpp

        LZ77/LZ77Encoder.cpp
        LZ77/LZ77Encoder.h
)

add_executable(Timing timing.cpp)
target_link_libraries(Timing KDZ1)

add_executable(Entropy entropy.cpp)
target_link_libraries(Entropy KDZ1)

add_executable(NSimb nsimb.cpp)

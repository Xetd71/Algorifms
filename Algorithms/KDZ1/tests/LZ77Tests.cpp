//
// Created by Ivan on 3/24/2018.
//

#include <gtest/gtest.h>
#include <fstream>

#include "../src/LZ77/LZ77Encoder.h"

const std::string res = "../../resources/files/";
const std::string FanoDir = "../../tests/resources/LZ77/";

TEST(LZ77Encoder, encodeFile)
{
    LZ77Encoder he(4 * 1024, 5 * 1024);
    he.encodeFile(res + "01.pdf", FanoDir + "01.lz77");
    he.decodeFile(FanoDir + "01.lz77", FanoDir + "01.pdf");

//    he.encodeFile(res + "test.txt", FanoDir + "test.lz77");
//    he.decodeFile(FanoDir + "test.lz77", FanoDir + "test.txt");

//    he.encodeFile(res + "28.png", FanoDir + "28.lz77");
//    he.decodeFile(FanoDir + "28.lz77", FanoDir + "28.png");

//    he.encodeFile(res + "02", FanoDir + "02.lz77");
//    he.decodeFile(FanoDir + "02.lz77", FanoDir + "02");
//
//    he.encodeFile(res + "26.gif", FanoDir + "26.lz77");
//    he.decodeFile(FanoDir + "26.lz77", FanoDir + "26.gif");
}
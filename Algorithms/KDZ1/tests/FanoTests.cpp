//
// Created by Ivan on 3/22/2018.
//

#include <gtest/gtest.h>
#include <fstream>

#include "../src/TableEncoders/Fano/FanoEncoder.h"

const std::string res = "../../resources/files/";
const std::string FanoDir = "../../tests/resources/Fano/";

TEST(FanoEncoder, encodeFile)
{
    FanoEncoder he;
    he.encodeFile(res + "01.pdf", FanoDir + "01.fano");
    he.decodeFile(FanoDir + "01.fano", FanoDir + "01.pdf");
}

TEST(FanoEncoder, testEncode)
{
    FanoEncoder he;
    he.encodeFile(res + "test.txt", FanoDir + "test.fano");
    he.decodeFile(FanoDir + "test.fano", FanoDir + "test.txt");
}

TEST(FanoEncoder, encodeFile2)
{
    FanoEncoder he;
    he.encodeFile(res + "26.gif", FanoDir + "26.fano");
    he.decodeFile(FanoDir + "26.fano", FanoDir + "26.gif");
}
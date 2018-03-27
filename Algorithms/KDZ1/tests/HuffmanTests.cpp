//
// Created by Ivan on 3/15/2018.
//

#include <gtest/gtest.h>

#include "../src/TableEncoders/Huffman/HuffmanEncoder.h"

const std::string res = "../../resources/files/";
const std::string FanoDir = "../../tests/resources/Huffman/";

TEST(HuffmanEncoder, encodeFile)
{
    HuffmanEncoder he;
    he.encodeFile("../../tests/resources/test.txt", FanoDir + "test.huff");
}

TEST(HuffmanEncoder, decodeFile)
{
    HuffmanEncoder he;
    he.decodeFile(FanoDir + "test.huff", FanoDir + "test.txt");
}

TEST(HuffmanEncoder, tmp)
{
    HuffmanEncoder he;
    he.encodeFile(res + "01", FanoDir + "01.huff");
    he.decodeFile(FanoDir + "01.huff", FanoDir + "01.pdf");
}

TEST(HuffmanEncoder, decodeFile3)
{
    HuffmanEncoder he;
    he.encodeFile(res + "03", FanoDir + "03.huff");
    he.decodeFile(FanoDir + "03.huff", FanoDir + "03.doc");
}

TEST(HuffmanEncoder, decodeFile5)
{
    HuffmanEncoder he;
    he.encodeFile(res + "05", FanoDir + "05.huff");
    he.decodeFile(FanoDir + "05.huff", FanoDir + "05.txt");
}

TEST(HuffmanEncoder, decodeFile4)
{
    HuffmanEncoder he;
    he.encodeFile(res + "04", FanoDir + "04.huff");
    he.decodeFile(FanoDir + "04.huff", FanoDir + "04.docx");
}

TEST(HuffmanEncoder, decodeFile9)
{
    HuffmanEncoder he;
    he.encodeFile(res + "09", FanoDir + "09.huff");
    he.decodeFile(FanoDir + "09.huff", FanoDir + "09.pdf");
}

TEST(HuffmanEncoder, decodeFile20)
{
    HuffmanEncoder he;
    he.encodeFile(res + "20", FanoDir + "20.huff");
    he.decodeFile(FanoDir + "20.huff", FanoDir + "20.jpeg");
}
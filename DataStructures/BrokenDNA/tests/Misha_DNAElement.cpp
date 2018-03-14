#include <gtest/gtest.h>
#include "../src/dna_element.h"

TEST(DNA_Element, simplest)
{
    DNAElement element;
}

TEST(DNA_Element, ReadFromStr)
{
    DNAElement element = DNAElement();
    element.readFromString("a1:A");

    EXPECT_EQ(element.id, "a");
    EXPECT_EQ(element.number, 1);
    EXPECT_EQ((char)element.base, 'A');
}

TEST(DNA_Element, ConstructorFromStr)
{
    DNAElement element = DNAElement("a1:A");

    EXPECT_EQ(element.id, "a");
    EXPECT_EQ(element.number, 1);
    EXPECT_EQ((char)element.base, 'A');
}


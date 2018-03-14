#include <gtest/gtest.h>
#include "../src/SkipList.h"

TEST(SkipListStudentTests, simpleTest)
{
    SkipList<int, int, 5> list;
}

TEST(SkipListStudentTests, copyConstructor)
{
    SkipList<int, int, 2> list;
    list.insert(1, 1);
    list.insert(2, 2);
    list.insert(3, 3);

    SkipList<int, int, 2> list2 = list;

    list.remove(list.findFirst(1));
    list.remove(list.findFirst(2));
    list.remove(list.findFirst(3));

    NodeSkipList<int, int, 2>* n = list2.findFirst(2);
    EXPECT_EQ(2, n->m_value);
    EXPECT_EQ(2, n->m_key);

    list2.remove(list2.findFirst(2));
    n = list2.findFirst(3);
    EXPECT_EQ(3, n->m_value);
    EXPECT_EQ(3, n->m_key);
}

TEST(SkipListStudentTests, assignmentOperator)
{
    SkipList<int, int, 2> list, list2;
    list.insert(1, 1);
    list.insert(2, 2);
    list.insert(3, 3);
    list.insert(2, 12);

    list2 = list;

    list.remove(list.findFirst(1));
    list.remove(list.findFirst(2));
    list.remove(list.findFirst(3));

    NodeSkipList<int, int, 2>* n = list2.findFirst(2);
    EXPECT_EQ(2, n->m_value);
    EXPECT_EQ(2, n->m_key);

    list2.remove(list2.findFirst(2));
    n = list2.findFirst(3);
    EXPECT_EQ(3, n->m_value);
    EXPECT_EQ(3, n->m_key);

    EXPECT_EQ(nullptr, list2.findFirst(2));
}

TEST(SkipListStudentTests, insert)
{
    SkipList<int, int, 5> list;

    for(int i = 0; i < 100; ++i)
        list.insert(i, i);

    EXPECT_EQ(10, list.findFirst(10)->m_value);
    EXPECT_EQ(93, list.findFirst(93)->m_value);
    EXPECT_EQ(48, list.findFirst(48)->m_value);
}

TEST(SkipListStudentTests, findFirst)
{
    SkipList<int, int, 5> list;

    for(int i = 0; i < 100; ++i)
        list.insert(i, i);

    EXPECT_EQ(13, list.findFirst(13)->m_value);
    EXPECT_EQ(88, list.findFirst(88)->m_value);
    EXPECT_EQ(23, list.findFirst(23)->m_value);

    EXPECT_EQ(nullptr, list.findFirst(102));
    EXPECT_EQ(nullptr, list.findFirst(1008));
}

TEST(SkipListStudentTests, findLastLessThan)
{
    SkipList<int, int, 5> list;

    for(int i = 0; i < 100; ++i)
        list.insert(i, i);

    EXPECT_EQ(12, list.findLastLessThan(13)->m_value);
    EXPECT_EQ(87, list.findLastLessThan(88)->m_value);
    EXPECT_EQ(22, list.findLastLessThan(23)->m_value);

    EXPECT_EQ(99, list.findLastLessThan(100)->m_value);
    EXPECT_EQ(99, list.findLastLessThan(102)->m_value);
    EXPECT_EQ(99, list.findLastLessThan(1008)->m_value);

    EXPECT_EQ(list.getPreHead(), list.findLastLessThan(0));
    EXPECT_EQ(list.getPreHead(), list.findLastLessThan(-13));
    EXPECT_EQ(list.getPreHead(), list.findLastLessThan(-56));
}

TEST(SkipListStudentTests, remove)
{
    SkipList<int, int, 3> list;

    for(int i = 0; i < 20; ++i)
        list.insert(i, i);

    NodeSkipList<int, int, 3>* element = list.findFirst(10);
    EXPECT_NE(nullptr, element);
    EXPECT_EQ(10, list.findLastLessThan(11)->m_value);

    list.remove(element);
    element = list.findFirst(10);
    EXPECT_EQ(nullptr, element);
    EXPECT_EQ(9, list.findLastLessThan(11)->m_value);

    EXPECT_THROW(list.remove(new NodeSkipList<int, int, 3>(5, 5)), std::invalid_argument);
    EXPECT_THROW(list.remove(nullptr), std::invalid_argument);
    EXPECT_THROW(list.remove(list.getPreHead()), std::invalid_argument);
}
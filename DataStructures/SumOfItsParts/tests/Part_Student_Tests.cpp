/**
 *  \file
 *  \brief тесты к классу Part
 *  \author Чуев Иван БПИ163
 *  \date 30.11.2017
 */

#include <gtest/gtest.h>
#include "../src/Parts.h"

TEST(Part_Student, simpleTest)
{
    Part p = Part("Simple name");

    EXPECT_EQ("Simple name", p.name);
    EXPECT_EQ(nullptr, p.parent);
    EXPECT_EQ(0, p.subparts.size());
}

TEST(Part_Student, addSubParts)
{
    Part* p1 = new Part("Simple name #1");
    Part* p2 = new Part("Simple name #2");

    EXPECT_EQ("Simple name #1", p1->name);
    EXPECT_EQ(nullptr, p1->parent);
    EXPECT_EQ(0, p1->subparts.size());

    EXPECT_EQ("Simple name #2", p2->name);
    EXPECT_EQ(nullptr, p2->parent);
    EXPECT_EQ(0, p2->subparts.size());

    p2->addSubPart(p1, 9);
    EXPECT_EQ(p2, p1->parent);
    EXPECT_EQ(1, p2->subparts.size());
    EXPECT_EQ(9, p2->subparts[p1]);

    delete p1, p2;
}

TEST(Part_Student, countHowMany)
{
    Part* p1 = new Part("p1");
    Part* p11 = new Part("p11");
    Part* p12 = new Part("p12");
    Part* p111 = new Part("p111");

    EXPECT_EQ(0, p1->count_howmany(p11));
    EXPECT_EQ(0, p1->count_howmany(p12));
    EXPECT_EQ(0, p1->count_howmany(p111));
    EXPECT_EQ(0, p11->count_howmany(p111));

    p1->addSubPart(p11, 6);
    p1->addSubPart(p12, 3);
    p11->addSubPart(p111, 8);

    EXPECT_EQ(48, p1->count_howmany(p111));
    EXPECT_EQ(8, p11->count_howmany(p111));
    EXPECT_EQ(6, p1->count_howmany(p11));
    EXPECT_EQ(3, p1->count_howmany(p12));

    delete p1, p11, p12, p111;
}

TEST(Part_Student, countHowManyUp)
{
    Part* p1 = new Part("p1");
    Part* p11 = new Part("p11");
    Part* p12 = new Part("p12");
    Part* p111 = new Part("p111");

    EXPECT_EQ(0, p1->count_howmany(p11));
    EXPECT_EQ(0, p1->count_howmany(p12));
    EXPECT_EQ(0, p1->count_howmany(p111));
    EXPECT_EQ(0, p11->count_howmany(p111));

    p1->addSubPart(p11, 6);
    p1->addSubPart(p12, 3);
    p11->addSubPart(p111, 8);

    EXPECT_EQ(48, p1->count_howmanyUp(p111));
    EXPECT_EQ(8, p11->count_howmanyUp(p111));
    EXPECT_EQ(6, p1->count_howmanyUp(p11));
    EXPECT_EQ(3, p1->count_howmanyUp(p12));

    delete p1, p11, p12, p111;
}
/**
 *  \file
 *  \brief тесты к классу NameContainer
 *  \author Чуев Иван БПИ163
 *  \date 30.11.2017
 */

#include <gtest/gtest.h>
#include "../src/Parts.h"

TEST(NameContainer_Student, simpleTest)
{
    NameContainer nc;
}

TEST(NameContainer_Student, addPart)
{
    NameContainer nc;
    nc.add_part("1", 6, "11");
    nc.add_part("1", 3, "12");
    nc.add_part("11", 8, "111");

    Part* p1 = nc.lookup("1");
    Part* p11 = nc.lookup("11");
    Part* p12 = nc.lookup("12");
    Part* p111 = nc.lookup("111");

    EXPECT_EQ("1", p1->name);
    EXPECT_EQ("11", p11->name);
    EXPECT_EQ("12", p12->name);
    EXPECT_EQ("111", p111->name);

    EXPECT_EQ(nullptr, p1->parent);
    EXPECT_EQ(p1, p11->parent);
    EXPECT_EQ(p1, p12->parent);
    EXPECT_EQ(p11, p111->parent);

    EXPECT_EQ(48, p1->count_howmany(p111));
    EXPECT_EQ(8, p11->count_howmany(p111));
    EXPECT_EQ(6, p1->count_howmany(p11));
    EXPECT_EQ(3, p1->count_howmany(p12));
}

TEST(NameContainer_Student, lookUp)
{
    NameContainer nc;
    nc.add_part("1", 6, "11");

    Part* p1 = nc.lookup("1");
    Part* p11 = nc.lookup("11");
    Part* p12 = nc.lookup("12");
    EXPECT_NE(nullptr, p1);
    EXPECT_NE(nullptr, p11);
    EXPECT_NE(nullptr, p12);

    EXPECT_EQ(nullptr, p12->parent);
    EXPECT_EQ(0, p12->subparts.size());
}

TEST(NameContainer_Student, swap)
{
    NameContainer nc1, nc2;
    nc1.add_part("1", 6, "11");
    swap(nc1, nc2);

    EXPECT_EQ(6, nc2.lookup("1")->count_howmany(nc2.lookup("11")));
    EXPECT_EQ(0, nc1.lookup("1")->count_howmany(nc1.lookup("11")));
}

TEST(NameContainer_Student, copyConstructor)
{
    NameContainer nc1;
    nc1.add_part("1", 6, "11");
    nc1.add_part("1", 3, "12");
    nc1.add_part("11", 8, "111");


    NameContainer nc2 = nc1;

    Part* p1 = nc2.lookup("1");
    Part* p11 = nc2.lookup("11");
    Part* p12 = nc2.lookup("12");
    Part* p111 = nc2.lookup("111");

    EXPECT_NE(p1, nc1.lookup("1"));
    EXPECT_NE(p11, nc1.lookup("11"));
    EXPECT_NE(p12, nc1.lookup("12"));
    EXPECT_NE(p111, nc1.lookup("111"));


    EXPECT_EQ("1", p1->name);
    EXPECT_EQ("11", p11->name);
    EXPECT_EQ("12", p12->name);
    EXPECT_EQ("111", p111->name);

    EXPECT_EQ(nullptr, p1->parent);
    EXPECT_EQ(p1, p11->parent);
    EXPECT_EQ(p1, p12->parent);
    EXPECT_EQ(p11, p111->parent);


    EXPECT_EQ(48, p1->count_howmany(p111));
    EXPECT_EQ(8, p11->count_howmany(p111));
    EXPECT_EQ(6, p1->count_howmany(p11));
    EXPECT_EQ(3, p1->count_howmany(p12));
}

TEST(NameContainer_Student, copyOperator)
{
    NameContainer nc1, nc2;
    nc1.add_part("1", 6, "11");
    nc1.add_part("1", 3, "12");
    nc1.add_part("11", 8, "111");


    nc2 = nc1;

    Part* p1 = nc2.lookup("1");
    Part* p11 = nc2.lookup("11");
    Part* p12 = nc2.lookup("12");
    Part* p111 = nc2.lookup("111");

    EXPECT_NE(p1, nc1.lookup("1"));
    EXPECT_NE(p11, nc1.lookup("11"));
    EXPECT_NE(p12, nc1.lookup("12"));
    EXPECT_NE(p111, nc1.lookup("111"));


    EXPECT_EQ("1", p1->name);
    EXPECT_EQ("11", p11->name);
    EXPECT_EQ("12", p12->name);
    EXPECT_EQ("111", p111->name);

    EXPECT_EQ(nullptr, p1->parent);
    EXPECT_EQ(p1, p11->parent);
    EXPECT_EQ(p1, p12->parent);
    EXPECT_EQ(p11, p111->parent);


    EXPECT_EQ(48, p1->count_howmany(p111));
    EXPECT_EQ(8, p11->count_howmany(p111));
    EXPECT_EQ(6, p1->count_howmany(p11));
    EXPECT_EQ(3, p1->count_howmany(p12));
}
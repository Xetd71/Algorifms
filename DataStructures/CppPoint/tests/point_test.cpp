#include <gtest/gtest.h>


#include "../src/xipoint.h"

TEST(XiPoint, simplest)
{
    using namespace xi;

    Point p1;
    Point p2(1, 1);
}


TEST(XiPoint, constructorDef)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

}

TEST(XiPoint, set1)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

    p1.setX(42);
    p1.setY(13);
    EXPECT_EQ(42, p1.getX());
    EXPECT_EQ(13, p1.getY());

}


TEST(XiPoint, shift1)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

    p1.shift(15);
    EXPECT_EQ(15, p1.getX());
    EXPECT_EQ(15, p1.getY());
}


TEST(XiPoint, shift4)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

    Point p2(5, 10);
    EXPECT_EQ(5, p2.getX());
    EXPECT_EQ(10, p2.getY());

}

TEST(XiPoint, shiftByPoint)
{
    using namespace xi;
    Point p1 = Point(3, 5);
    p1.shift(Point(4, 6));

    EXPECT_EQ(7, p1.getX());
    EXPECT_EQ(11, p1.getY());
}


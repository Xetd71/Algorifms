#include <gtest/gtest.h>
#include "../src/xipoint.h"

TEST(XiPointArray, simplest)
{
    using namespace xi;

    PointArray ar1;
}


TEST(XiPointArray, properInit)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());
}


TEST(XiPointArray, initByArray)
{

    using namespace xi;

    Point testAr[] = {Point(1, 1), Point(2, 2), Point(3, 3)};
    PointArray::Uint testArSize = sizeof(testAr) / sizeof(testAr[0]);

    PointArray ar1(testAr, testArSize);
    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(testArSize, ar1.getSize());

    EXPECT_EQ(1, ar1.get(0)->getX());
    EXPECT_EQ(1, ar1.get(0)->getY());
    EXPECT_EQ(2, ar1.get(1)->getX());
    EXPECT_EQ(2, ar1.get(1)->getY());
    EXPECT_EQ(3, ar1.get(2)->getX());
    EXPECT_EQ(3, ar1.get(2)->getY());
}


TEST(XiPointArray, clear1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());

    Point p1(10, 15);
    ar1.append(p1);

    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(1, ar1.getSize());

    ar1.clear();

}


TEST(XiPointArray, remove1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());

    ar1.append(Point(0, 0));
    ar1.append(Point(1, 1));
    ar1.append(Point(2, 2));
    ar1.append(Point(3, 3));
    ar1.append(Point(4, 4));


    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(5, ar1.getSize());

    ar1.remove(0);
    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(4, ar1.getSize());

}

TEST(XiPointArray, get1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());

    EXPECT_EQ(nullptr, ar1.get(0));
    EXPECT_EQ(nullptr, ar1.get(1));

}


TEST(XiPointArray, insert1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());

    Point p1(10, 15);
    ar1.insert(p1, 0);

    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(1, ar1.getSize());
}

TEST(XiPointArray, qwerty)
{
    using namespace xi;

    Point testAr[] = {Point(1, 2), Point(4, 3), Point(5, 7)};
    PointArray arr = PointArray(PointArray(testAr, 2));

    Point p = *arr.get(1);
    EXPECT_EQ(2, arr.getSize());
    EXPECT_EQ(1, arr.get(0)->getX());
    EXPECT_EQ(2, arr.get(0)->getY());
    EXPECT_EQ(4, arr.get(1)->getX());
    EXPECT_EQ(3, arr.get(1)->getY());

    arr.append(Point(1, 1));
    arr.append(Point(1, 1));

    EXPECT_EQ(4, arr.getSize());
    arr.insert(Point(0, 0), 0);
    EXPECT_EQ(0, arr.get(0)->getX());
    EXPECT_EQ(0, arr.get(0)->getY());

    arr.remove(0);
    arr.remove(2);
    arr.remove(0);
    Point p1 = *arr.get(0);
}

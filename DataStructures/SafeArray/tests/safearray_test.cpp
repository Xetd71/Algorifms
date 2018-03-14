////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::SafeArray class
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      23.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "../src/safearray.h"
#include <iostream> 


TEST(StackArray, simplest)
{
    using namespace xi;

    SafeArray<int> sa;
    // SafeArray<void> st1;     // ошибка: тип void не может быть инстанцирован в объект!
}


TEST(StackArray, DefConstructor)
{
    using namespace xi;

    SafeArray<int> sa;
    EXPECT_EQ(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 0);
}


TEST(StackArray, InitConstructor1)
{
    using namespace xi;

    SafeArray<int> sa(3);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 3);
}


TEST(StackArray, IndexOper1)
{
    using namespace xi;

    SafeArray<int> sa(3);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 3);

    sa[0] = 0;
    sa[1] = 1;
    sa[2] = 2;

    // out of range:
    EXPECT_THROW(sa[3] = 3, std::out_of_range);
}


TEST(StackArray, IndexConstOper1)
{
    using namespace xi;

    SafeArray<int> sa(1);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 1);

    sa[0] = 0;
    EXPECT_EQ(sa[0], 0);

    const int el0 = sa[0];
    EXPECT_EQ(el0, sa[0]);

    // out of range:
    EXPECT_THROW(sa[1], std::out_of_range); // да, это тоже выражение!
}

TEST(StackArray, CopyConstr1)
{
    using namespace xi;

    SafeArray<int> sa(1);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 1);

    SafeArray<int> sb = sa;
    EXPECT_NE(sb.getRawPtr(), nullptr);
    EXPECT_EQ(sb.getCapacity(), 1);

    // корректность конструктора копирования
    ASSERT_NE(sa.getRawPtr(), sb.getRawPtr());
}


TEST(StackArray, AssignOper1)
{
    using namespace xi;

    SafeArray<int> sa(1);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 1);

    SafeArray<int> sb;
    EXPECT_EQ(sb.getRawPtr(), nullptr);
    EXPECT_EQ(sb.getCapacity(), 0);

    // копируем
    sb = sa;

    EXPECT_NE(sb.getRawPtr(), nullptr);
    EXPECT_EQ(sb.getCapacity(), 1);

    // корректность операции копирования
    ASSERT_NE(sa.getRawPtr(), sb.getRawPtr());
}

TEST(StackArray, AssertNullConstructor) {
    using namespace xi;

    SafeArray<int> sa1(0);

    EXPECT_EQ(sa1.getRawPtr(), nullptr);
    EXPECT_EQ(sa1.getCapacity(), 0);
}


TEST(StackArray, AssertNullAssign) {
    using namespace xi;

    const size_t length = 5;
    SafeArray<int> a;
    SafeArray<int> a1(length);
    SafeArray<int> a2(length);
    for(size_t i = 0; i < length; i++) {
        a1[i] = i;
        a2[i] = i * i;
    }

    a1 = a;
    EXPECT_EQ(a1.getRawPtr(), nullptr);
    EXPECT_EQ(a1.getCapacity(), 0);

    a = a2;
    EXPECT_NE(a.getRawPtr(), nullptr);
    EXPECT_EQ(a.getCapacity(), length);
    for(size_t i = 0; i < length; i++) {
        EXPECT_EQ(a[i], i * i);
    }
}


TEST(StackArray, AssertNullCopy) {
    using namespace xi;

    const size_t length = 5;
    SafeArray<int> a;
    SafeArray<int> a1 = a;
    EXPECT_EQ(a1.getRawPtr(), nullptr);
    EXPECT_EQ(a1.getCapacity(), 0);

    a = SafeArray<int>(5);
    for(size_t i = 0; i < length; i++) {
        a[i] = i;
    }
    a1 = a;
    EXPECT_NE(a1.getRawPtr(), nullptr);
    EXPECT_EQ(a1.getCapacity(), length);
    for(size_t i = 0; i < length; i++) {
        EXPECT_EQ(a1[i], i);
    }
}


TEST(StackArray, AssertAssign) {
    using namespace xi;

    const size_t length = 5;
    SafeArray<int> a(length);
    for(size_t i = 0; i < length; i++)
        a[i] = i;

    SafeArray<int> a1;
    a1 = a;

    ASSERT_NE(a.getRawPtr(), a1.getRawPtr());
    EXPECT_EQ(a1.getCapacity(), length);
    for(size_t i = 0; i < length; i++)
        EXPECT_EQ(a1[i], i);
}


TEST(StackArray, AssertCopy) {
    using namespace xi;

    const size_t length = 5;
    SafeArray<int> a(length);
    for(size_t i = 0; i < length; i++)
        a[i] = i;

    SafeArray<int> a1 = a;

    ASSERT_NE(a.getRawPtr(), a1.getRawPtr());
    EXPECT_EQ(a1.getCapacity(), length);
    for(size_t i = 0; i < length; i++)
        EXPECT_EQ(a1[i], i);
}


TEST(StackArray, AssertSwap) {
    using namespace xi;

    const size_t length = 5;
    SafeArray<int> a(length);
    SafeArray<int> a1;

    for(size_t i = 0; i < length; i++)
        a[i] = i;
    swap(a, a1);

    EXPECT_EQ(a.getRawPtr(), nullptr);
    EXPECT_EQ(a.getCapacity(), 0);

    EXPECT_NE(a1.getRawPtr(), nullptr);
    EXPECT_EQ(a1.getCapacity(), length);
    for(size_t i = 0; i < length; i++)
        EXPECT_EQ(a1[i], i);
}


TEST(StackArray, Stas_SwapOper) {
    using namespace xi;

    SafeArray<int> sa(1);
    sa[0] = 1;
    SafeArray<int> sb(1);
    sb[0] = 2;
    swap(sa, sb);
    EXPECT_EQ(sa[0], 2);
    EXPECT_EQ(sb[0], 1);

}


TEST(StackArray, Stas_CopyConstr1) {
    using namespace xi;

    SafeArray<int> sa(1);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 1);
    sa[0] = 1;
    SafeArray<int> sb = sa;

    EXPECT_NE(sb.getRawPtr(), nullptr);
    EXPECT_EQ(sb.getCapacity(), 1);

    // корректность конструктора копирования
    ASSERT_NE(sa.getRawPtr(), sb.getRawPtr());
    EXPECT_EQ(sa.getCapacity(), sb.getCapacity());
    EXPECT_EQ(true, std::equal(sa.getRawPtr(), sa.getRawPtr() + sa.getCapacity(), sb.getRawPtr()));

    sb[0] = 2;
    EXPECT_EQ(sa.getCapacity(), sb.getCapacity());
    EXPECT_NE(true, std::equal(sa.getRawPtr(), sa.getRawPtr() + sa.getCapacity(), sb.getRawPtr()));

}
#include <gtest/gtest.h>
#include "../src/NiceStack.h"

TEST(NiceStack, simpleTest)
{
    NiceStack<int> stack = NiceStack<int>(5);
}

TEST(NiceStack, assert_size)
{
    NiceStack<int> stack = NiceStack<int>(5);

    EXPECT_EQ(stack.size(), 0);

    stack.push(1);
    EXPECT_EQ(stack.size(), 1);

    stack.pop();
    EXPECT_EQ(stack.size(), 0);
}

TEST(NiceStack, assert_pushAndPop)
{
    NiceStack<int> stack = NiceStack<int>(5);

    for(int i = 0; i < 5; ++i)
        stack.push(i);
    EXPECT_THROW(stack.push(6), std::out_of_range);

    for(int j = 4; j >= 0; --j)
        EXPECT_EQ(stack.pop(), j);
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(NiceStack, assert_getMinimum)
{
    NiceStack<int> stack = NiceStack<int>(5);

    EXPECT_THROW(stack.getMinimum(), std::out_of_range);

    stack.push(5);
    EXPECT_EQ(stack.getMinimum(), 5);

    stack.push(3);
    EXPECT_EQ(stack.getMinimum(), 3);

    stack.push(5);
    EXPECT_EQ(stack.getMinimum(), 3);

    stack.push(1);
    EXPECT_EQ(stack.getMinimum(), 1);

    stack.pop();
    EXPECT_EQ(stack.getMinimum(), 3);
}
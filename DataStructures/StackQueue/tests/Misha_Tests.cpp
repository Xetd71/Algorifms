#include <gtest/gtest.h>
#include "../src/NiceStack.h"
#include "../src/NiceQueue.h"

TEST(NiceStack, Constructor)
{
    NiceStack<int> niceStack(20);
}

TEST(NiceStack, Size)
{
    NiceStack<int> niceStack(20);
    EXPECT_EQ(niceStack.size(), 0);
    niceStack.push(1);
    EXPECT_EQ(niceStack.size(), 1);
}

TEST(NiceStack, PushElement)
{
    NiceStack<int> niceStack(1);
    niceStack.push(1);
    EXPECT_EQ(niceStack.size(), 1);
    EXPECT_THROW(niceStack.push(2), std::out_of_range);
}

TEST(NiceStack, PopElement)
{
    NiceStack<int> niceStack(3);
    EXPECT_THROW(niceStack.pop(), std::out_of_range);
    niceStack.push(1);
    niceStack.push(2);
    EXPECT_EQ(niceStack.pop(), 2);
    EXPECT_EQ(niceStack.size(), 1);
    EXPECT_EQ(niceStack.pop(), 1);
    EXPECT_EQ(niceStack.size(), 0);
}

TEST(NiceStack, GetMinimum)
{
    NiceStack<int> niceStack(5);
    EXPECT_THROW(niceStack.getMinimum(), std::out_of_range);
    niceStack.push(5);
    EXPECT_EQ(niceStack.getMinimum(), 5);
    niceStack.push(7);
    EXPECT_EQ(niceStack.getMinimum(), 5);
    niceStack.push(2);
    EXPECT_EQ(niceStack.getMinimum(), 2);
    niceStack.push(1);
    EXPECT_EQ(niceStack.getMinimum(), 1);
    niceStack.push(6);
    EXPECT_EQ(niceStack.getMinimum(), 1);
}

TEST(NiceStack, constructor)
{
    NiceStack<int> st(2);
}

TEST(NiceStack, push)
{
    NiceStack<int> st(2);
    st.push(234);
    EXPECT_EQ(234, st.pop());
    st.push(21);
    st.push(12);
    EXPECT_THROW(st.push(2), std::out_of_range);
}

TEST(NiceStack, pop)
{
    NiceStack<int> st(2);
    EXPECT_THROW(st.pop(), std::out_of_range);
    st.push(234);
    EXPECT_EQ(234, st.pop());
}

TEST(NiceStack, size)
{
    NiceStack<int> st(2);
    EXPECT_EQ(st.size(), 0);
    st.push(234);
    EXPECT_EQ(st.size(), 1);
    st.push(21);
    EXPECT_EQ(st.size(), 2);
}

TEST(NiceStack, getMinimum)
{
    NiceStack<int> st(2);
    EXPECT_THROW(st.getMinimum(), std::out_of_range);
    st.push(234);
    st.push(21);
    EXPECT_EQ(st.getMinimum(), 21);
}

TEST(NiceQueue, constructor)
{
    NiceQueue<int> qu(2);
}

TEST(NiceQueue, size)
{
    NiceQueue<int> qu(2);
    EXPECT_EQ(qu.size(), 0);
    qu.enq(3);
    EXPECT_EQ(qu.size(), 1);
    qu.deq();
    EXPECT_EQ(qu.size(), 0);

}

TEST(NiceQueue, enq)
{
    NiceQueue<int> qu(3);
    qu.enq(3);
    EXPECT_EQ(qu.deq(), 3);
    qu.enq(3);
    qu.enq(2);
    qu.enq(5);
    EXPECT_THROW(qu.enq(10), std::out_of_range);
}

TEST(NiceQueue, deq)
{
    NiceQueue<int> qu(3);
    EXPECT_THROW(qu.deq(), std::out_of_range);
    qu.enq(3);
    EXPECT_EQ(qu.deq(), 3);
}

TEST(NiceQueue, getMinimum)
{
    NiceQueue<int> qu(4);
    EXPECT_THROW(qu.getMinimum(), std::out_of_range);
    qu.enq(10);
    qu.enq(3);
    qu.enq(2);
    qu.enq(5);
    EXPECT_EQ(qu.getMinimum(), 2);
}
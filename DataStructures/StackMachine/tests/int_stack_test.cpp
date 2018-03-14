#include <gtest/gtest.h>


#include "../src/int_stack.h"


TEST(IntStack, simplest)
{
    using namespace xi;

    IntStack st;
}


TEST(IntStack, constr1)
{
    using namespace xi;

    IntStack st;

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());
}


TEST(IntStack, constr2)
{
    using namespace xi;

    IntStack st(1);                 // maximum stack size

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    st.push(42);                    // should be filled up here
    EXPECT_FALSE(st.isEmpty());
    EXPECT_TRUE(st.isFull());
}


TEST(IntStack, pushpop1)
{
    using namespace xi;

    IntStack st;
    EXPECT_TRUE(st.isEmpty());

    int v1 = 42;
    int v2 = 13;
    int v3 = 667;

    st.push(v1);
    EXPECT_FALSE(st.isEmpty());
    st.push(v2);
    st.push(v3);
    EXPECT_FALSE(st.isEmpty());

    // the reverse order of extraction is expected
    EXPECT_EQ(st.pop(), v3);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_EQ(st.pop(), v2);
    EXPECT_EQ(st.pop(), v1);
    EXPECT_TRUE(st.isEmpty());
}

TEST(IntStack, pushoverflow)
{
    using namespace xi;

    IntStack st(1);                 // maximum stack size

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    st.push(42);                    // should be filled up here
    EXPECT_FALSE(st.isEmpty());
    EXPECT_TRUE(st.isFull());


    // std::logic_error
    EXPECT_THROW(st.push(13), std::logic_error);
}

TEST(IntStack, popnothing)
{
    using namespace xi;

    IntStack st;

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    // std::logic_error
    EXPECT_THROW(st.pop(), std::logic_error);
}

TEST(IntStack, top1)
{
    using namespace xi;

    IntStack st(1);

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    int v1 = 42;
    st.push(v1);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_TRUE(st.isFull());

    EXPECT_EQ(st.top(), v1);
    EXPECT_FALSE(st.isEmpty());     // should still be full
    EXPECT_TRUE(st.isFull());

    EXPECT_EQ(st.pop(), v1);        // now it's empty
    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

}


TEST(IntStack, clear1)
{
    using namespace xi;

    IntStack st(2);

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    st.push(42);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    st.push(13);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_TRUE(st.isFull());

    st.clear();
    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());
}

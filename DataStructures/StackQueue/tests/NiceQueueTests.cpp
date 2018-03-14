#include <gtest/gtest.h>
#include "../src/NiceQueue.h"

TEST(NiceQueue, simpleTest)
{
    NiceQueue<int> queue = NiceQueue<int>(5);
}

TEST(NiceQueue, assert_size)
{
    NiceQueue<int> queue = NiceQueue<int>(5);

    EXPECT_EQ(queue.size(), 0);

    queue.enq(5);
    EXPECT_EQ(queue.size(), 1);

    queue.deq();
    EXPECT_EQ(queue.size(), 0);
}

TEST(NiceQueue, assert_enqAndDeq)
{
    NiceQueue<int> queue = NiceQueue<int>(5);

    for(int i = 0; i < 5; ++i)
        queue.enq(i);
    EXPECT_THROW(queue.enq(6), std::out_of_range);

    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(queue.deq(), i);
    EXPECT_THROW(queue.deq(), std::out_of_range);

}

TEST(NiceQueue, assert_getMinimum)
{
    NiceQueue<int> queue = NiceQueue<int>(5);

    EXPECT_THROW(queue.getMinimum(), std::out_of_range);

    queue.enq(1);
    EXPECT_EQ(queue.getMinimum(), 1);

    queue.enq(7);
    EXPECT_EQ(queue.getMinimum(), 1);

    queue.enq(3);
    EXPECT_EQ(queue.getMinimum(), 1);

    queue.deq();
    EXPECT_EQ(queue.getMinimum(), 3);

    queue.enq(2);
    EXPECT_EQ(queue.getMinimum(), 2);
}
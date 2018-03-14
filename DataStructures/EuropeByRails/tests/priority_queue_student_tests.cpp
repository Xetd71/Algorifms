/*
 * \file
 * \brief тесты для класса PriorityQueue
 * \author Чуев Иван БПИ163
 * \date 05.11.2017
 */


#include <gtest/gtest.h>
#include "../src/priority_queue.h"

TEST(PriorityQueue_StudentTests, simpleTest)
{
    PriorityQueue<int> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);
    EXPECT_EQ(1, pq.pop());
    EXPECT_EQ(2, pq.pop());
    EXPECT_EQ(3, pq.pop());
}

TEST(PriorityQueue_StudentTests, setSize)
{
    PriorityQueue<int> pq(2);
    pq.push(2);
    pq.push(1);
    EXPECT_THROW(pq.push(0), std::out_of_range);
    EXPECT_EQ(1, pq.pop());
    EXPECT_EQ(2, pq.pop());
}

TEST(PriorityQueue_StudentTests, getSize)
{
    PriorityQueue<int> pq;
    pq.push(2);
    EXPECT_EQ(1, pq.size());
}

TEST(PriorityQueue_StudentTests, isEmpty)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(true, pq.isEmpty());

    pq.push(2);
    EXPECT_EQ(false, pq.isEmpty());

    pq.push(2);
    EXPECT_EQ(false, pq.isEmpty());

    pq.pop();
    pq.pop();
    EXPECT_EQ(true, pq.isEmpty());
}

TEST(PriorityQueue_StudentTests, isFull)
{
    PriorityQueue<int> pq(1);
    EXPECT_EQ(false, pq.isFull());

    pq.push(2);
    EXPECT_EQ(true, pq.isFull());

    pq.pop();
    EXPECT_EQ(false, pq.isFull());
}

TEST(PriorityQueue_StudentTests, push_pop)
{
    PriorityQueue<int> pq;

    pq.push(3);
    pq.push(7);
    pq.push(2);
    EXPECT_EQ(2, pq.pop());

    pq.push(5);
    EXPECT_EQ(3, pq.pop());

    pq.push(1);
    pq.push(10);
    EXPECT_EQ(1, pq.pop());

    pq.push(5);
    pq.push(7);
    EXPECT_EQ(5, pq.pop());

    EXPECT_EQ(5, pq.pop());
    EXPECT_EQ(7, pq.pop());
    EXPECT_EQ(7, pq.pop());
    EXPECT_EQ(10, pq.pop());
}

TEST(PriorityQueue_StudentTests, top)
{
    PriorityQueue<int> pq;
    pq.push(5);
    EXPECT_EQ(5, pq.top());
    EXPECT_EQ(1, pq.size());

    pq.push(3);
    EXPECT_EQ(3, pq.top());
    EXPECT_EQ(2, pq.size());

    pq.push(4);
    EXPECT_EQ(3, pq.top());
    EXPECT_EQ(3, pq.size());
}
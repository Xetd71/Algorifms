//
// Created by Stas Don on 31/10/2017.
//
#include <gtest/gtest.h>
#include <ctime>
#include "../src/priority_queue.h"
#include "../src/city.h"
#include "../src/rail_system.h"

TEST(PriorityQueue, simple)
{
    PriorityQueue<int> pq;
}


TEST(PriorityQueue, copyConstr)
{
    PriorityQueue<int> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);
    PriorityQueue<int> pq2(pq);
    EXPECT_EQ(pq.size(), pq2.size());
    pq.pop();
    EXPECT_EQ(pq.size() + 1, pq2.size());
}

TEST(PriorityQueue, assigmentOperator)
{
    PriorityQueue<int> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);
    PriorityQueue<int> pq2 = pq;
    EXPECT_EQ(pq.size(), pq2.size());
    pq.pop();
    EXPECT_EQ(pq.size() + 1, pq2.size());
}


TEST(PriorityQueue, push)
{
    PriorityQueue<int> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);

    while(pq.size() != 0)
        pq.pop();
}

TEST(PriorityQueue, pop)
{
    std::srand(std::time(nullptr));
    PriorityQueue<int> pq;
    for(int i = 0; i < 50; i++) {
        pq.push(std::rand() * 100);
    }
    int prev = pq.pop();
    while(pq.size() != 0) {
        int curr = pq.pop();
        EXPECT_LE(prev, curr);
    }
}

TEST(PriorityQueue, isEmpty)
{
    PriorityQueue<int> pq;
    EXPECT_TRUE(pq.isEmpty());
    pq.push(1);
    EXPECT_FALSE(pq.isEmpty());

}

TEST(PriorityQueue, isFull)
{
    PriorityQueue<int> pq(1);
    EXPECT_FALSE(pq.isFull());

    pq.push(1);
    EXPECT_TRUE(pq.isFull());
}

TEST(PriorityQueue, top)
{
    PriorityQueue<int> pq;
    pq.push(1);
    EXPECT_EQ(pq.top(), 1);
    EXPECT_EQ(pq.size(), 1);
}

TEST(PriorityQueue, size)
{
    PriorityQueue<int> pq;
    pq.push(1);
    EXPECT_EQ(pq.size(), 1);
}

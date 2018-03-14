//
// Created by Stas Don on 02/11/2017.
//

#include "gtest/gtest.h"
#include "../src/rail_system.h"

TEST(RailSystem, simplest)
{
    RailSystem railSystem("../../services.txt");
}

TEST(RailSystem, copyConstr)
{
    RailSystem railSystem1("../../services.txt");
    RailSystem railSystem2(railSystem1);
    Route route1 = railSystem1.getCheapestRoute("Lisbon", "Madrid");
    Route route2 = railSystem2.getCheapestRoute("Madrid", "Paris");
    EXPECT_EQ(75, route1.fee);
    EXPECT_EQ(450, route1.distance);
    EXPECT_EQ(30, route2.fee);
    EXPECT_EQ(2100, route2.distance);
}

TEST(RailSystem, assigmentOperator)
{
    RailSystem railSystem1("../../services.txt");
    RailSystem railSystem2 = railSystem1;
    Route route1 = railSystem1.getCheapestRoute("Lisbon", "Madrid");
    Route route2 = railSystem2.getCheapestRoute("Madrid", "Paris");
    EXPECT_EQ(75, route1.fee);
    EXPECT_EQ(450, route1.distance);
    EXPECT_EQ(30, route2.fee);
    EXPECT_EQ(2100, route2.distance);
}


TEST(RailSystem, Lisbon_Madrid)
{
    RailSystem railSystem("../../services.txt");
    Route route = railSystem.getCheapestRoute("Lisbon", "Madrid");
    EXPECT_EQ(75, route.fee);
    EXPECT_EQ(450, route.distance);
}

TEST(RailSystem, Madrid_Paris)
{
    RailSystem railSystem("../../services.txt");
    Route route = railSystem.getCheapestRoute("Madrid", "Paris");
    EXPECT_EQ(30, route.fee);
    EXPECT_EQ(2100, route.distance);
}

TEST(RailSystem, Lisbon_Vienna)
{
    RailSystem railSystem("../../services.txt");
    Route route = railSystem.getCheapestRoute("Lisbon", "Vienna");
    EXPECT_EQ(165, route.fee);
    EXPECT_EQ(3950, route.distance);
}
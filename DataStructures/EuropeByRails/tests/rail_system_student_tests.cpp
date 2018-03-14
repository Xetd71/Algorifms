/*
 * \file
 * \brief тесты для класса RailSystem
 * \author Чуев Иван БПИ163
 * \date 05.11.2017
 */

#include <gtest/gtest.h>
#include "../src/rail_system.h"

TEST(RailSystem_StudentTests, simpleTest)
{
    RailSystem rs("../../services.txt");
}

TEST(RailSystem_StudentTests, copyConstr)
{
    RailSystem* rs1 = new RailSystem("../../services.txt");
    Route route1 = rs1->getCheapestRoute("Rome", "Warsaw");

    RailSystem rs2 = *rs1;
    delete rs1;
    Route route2 = rs2.getCheapestRoute("Rome", "Warsaw");

    EXPECT_EQ(route1, route2);
}

TEST(RailSystem_StudentTests, cheapestRoute)
{
    RailSystem rs = RailSystem("../../services.txt");

    EXPECT_EQ(Route("Rome", "Warsaw", 175, 5200), rs.getCheapestRoute("Rome", "Warsaw"));
    EXPECT_EQ(Route("Madrid", "Paris", 30, 2100), rs.getCheapestRoute("Madrid", "Paris"));
    EXPECT_EQ(Route("Lisbon", "Madrid", 75, 450), rs.getCheapestRoute("Lisbon", "Madrid"));
    EXPECT_EQ(Route("Sofia", "Amsterdam", 210, 5400), rs.getCheapestRoute("Sofia", "Amsterdam"));
    EXPECT_EQ(Route("Sofia", "Paris", 65, 2300), rs.getCheapestRoute("Sofia", "Paris"));
}

TEST(RailSystem_StudentTests, is_valid_sity)
{
    RailSystem rs = RailSystem("../../services.txt");

    EXPECT_TRUE(rs.is_valid_city("Rome"));
    EXPECT_TRUE(rs.is_valid_city("Warsaw"));
    EXPECT_TRUE(rs.is_valid_city("Paris"));
    EXPECT_FALSE(rs.is_valid_city("123"));
}
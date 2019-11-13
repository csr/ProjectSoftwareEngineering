//============================================================================
// Name        : SubwaySimulationDomainTests.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
using namespace std;

#include "Subway.h"

class SubwaySimulationDomainTests: public ::testing::Test {
 protected:
  friend class Subway;
  // You should make the members protected s.t. they can be
  // accessed from sub-classes.

  Subway subway_;
};

/**
Tests the default constructor.
*/
TEST_F(SubwaySimulationDomainTests, DefaultConstructor) {
  EXPECT_TRUE(subway_.properlyInitialized());

  // verify post-condition
  EXPECT_EQ(0, subway_.getStationsCount());
  EXPECT_EQ(0, subway_.getTramsCount());
}

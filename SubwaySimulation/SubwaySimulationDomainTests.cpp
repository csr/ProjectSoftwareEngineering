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
#include <vector>
using namespace std;

#include "Subway.h"
#include "Station.h"
#include "Albatros.h"
#include "PCCTram.h"

class SubwaySimulationDomainTests: public ::testing::Test {
 protected:
  friend class Subway;
  Subway subway_;
};

/**
Tests the default constructor.
*/
TEST_F(SubwaySimulationDomainTests, DefaultConstructor) {
  EXPECT_TRUE(subway_.properlyInitialized());

  // verify post-condition
  EXPECT_EQ(0, subway_.getStationsCount());
}

/**
Tests getter/setter of Station.
*/
TEST_F(SubwaySimulationDomainTests, EmptyStationConstructor) {
  string name = "AntwerpenCentraal";
  StationType type = TypeStop;

  // Test constructor
  Station station = Station(name, type, {});

  EXPECT_TRUE(station.properlyInitialized());

  // Test getters
  EXPECT_EQ(name, station.getName());
  EXPECT_EQ(station.getTracksArray().size(), 0);
  EXPECT_EQ(station.getType(), type);
}

/**
Tests getter/setter of Tram.
*/
TEST_F(SubwaySimulationDomainTests, TramConstructor) {
//  Tram(int line, int capacity, int speed, string startStation)


  int line = 12, vehicle = 1;
  string stationName = "Antwerpen";

  // Test tram types
  Albatros albatrossTram = Albatros(line, stationName, vehicle);
  PCCTram pccTram = PCCTram(line, stationName, vehicle);

  int albatrossCapacity = 72, albatrossSpeed = 70;

  EXPECT_EQ(albatrossCapacity, albatrossTram.getMaxCapacity());
  EXPECT_EQ(albatrossSpeed, albatrossTram.getSpeed());

  int pccCapacity = 16, pccSpeed = 40;
  EXPECT_EQ(pccCapacity, pccTram.getMaxCapacity());
  EXPECT_EQ(pccSpeed, pccTram.getSpeed());

  // Test getters
  EXPECT_EQ(Albatross, albatrossTram.getType());
  EXPECT_EQ(PCC, pccTram.getType());
  EXPECT_EQ(line, albatrossTram.getLine());
  EXPECT_EQ(vehicle, albatrossTram.getVehicle());

  // Initial capacity should be zero
  EXPECT_EQ(0, albatrossTram.getCurrentCapacity());
}

/**
Tests Subway reset method.
*/
TEST_F(SubwaySimulationDomainTests, SubwayReset) {
  Station *station = new Station("AntwerpenCentraal", TypeStation, {});
  Albatros *tram = new Albatros(10, "AntwerpenCentraal", 20);

  subway_.importData({station}, {tram});

  EXPECT_EQ(1, subway_.getStationsCount());
  EXPECT_EQ(1, subway_.getTramsCount());

  subway_.reset();

  EXPECT_EQ(0, subway_.getStationsCount());
  EXPECT_EQ(0, subway_.getTramsCount());
}

/**
Verify whether unsatisfied pre-conditions indeed trigger failures
*/
TEST_F(SubwaySimulationDomainTests, ContractViolations) {
  vector<string> invalidStrings = {"", ".", " ", "-", "*", "Antwerpen Centraal"};

  std::vector<std::string>::iterator it;

  it = invalidStrings.begin();
  for (it = invalidStrings.begin(); it < invalidStrings.end(); it++) {
    string currentString = *it;
    Station newStation = Station(currentString, TypeStation, {});
  }
}
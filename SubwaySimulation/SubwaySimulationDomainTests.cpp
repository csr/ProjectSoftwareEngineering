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
  EXPECT_EQ(0, subway_.getTramsCount());
}

/**
Tests getter/setter of Station.
*/
TEST_F(SubwaySimulationDomainTests, StationConstructor) {
  string name = "AntwerpenCentraal", next = "AntwerpenBerchem", previous = "Roosendaal";
  int track = 23;
  Station station = Station(name, next, previous, track);
  EXPECT_TRUE(station.properlyInitialized());

  // Test getters
  EXPECT_EQ(name, station.getName());
  EXPECT_EQ(next, station.getNext());
  EXPECT_EQ(previous, station.getPrevious());
  EXPECT_EQ(track, station.getTrack());

  string newName = "MilanoCentrale", newNext = "MilanoGaribaldi", newPrevious = "MilanoCadorna";
  int newTrack = 54;

  // Test setters
  station.setName(newName);
  station.setNext(newNext);
  station.setPrevious(newPrevious);
  station.setTrack(newTrack);

  EXPECT_EQ(newName, station.getName());
  EXPECT_EQ(newNext, station.getNext());
  EXPECT_EQ(newPrevious, station.getPrevious());
  EXPECT_EQ(newTrack, station.getTrack());
}

/**
Tests getter/setter of Tram.
*/
TEST_F(SubwaySimulationDomainTests, TramConstructor) {
//  Tram(int line, int capacity, int speed, string startStation)
  int line = 12, capacity = 24, speed = 59;
  string startStation = "AntwerpenCentraal";
  Tram tram = Tram(line, capacity, speed, startStation);

  // Test getters
  EXPECT_EQ(line, tram.getLine());
  EXPECT_EQ(capacity, tram.getCapacity());
  EXPECT_EQ(speed, tram.getSpeed());
  EXPECT_EQ(startStation, tram.getStartStation());

  int newLine = 11, newCapacity = 304, newSpeed = 40;
  string newStartStation = "AntwerpenBerchem";

  // Test setters
  tram.setLine(newLine);
  tram.setCapacity(newCapacity);
  tram.setSpeed(newSpeed);
  tram.setStartStation(newStartStation);

  EXPECT_EQ(newLine, tram.getLine());
  EXPECT_EQ(newCapacity, tram.getCapacity());
  EXPECT_EQ(newSpeed, tram.getSpeed());
  EXPECT_EQ(newStartStation, tram.getStartStation());
}

/**
Tests Subway reset method.
*/
TEST_F(SubwaySimulationDomainTests, SubwayReset) {
  Station *station1 = new Station("A", "B", "C", 34);
  Station *station2 = new Station("C", "D", "E", 334);
  Tram *tram = new Tram(2, 43, 3, "A");

  subway_.importData({station1, station2}, {tram});
  EXPECT_EQ(2, subway_.getStationsCount());
  EXPECT_EQ(1, subway_.getTramsCount());

  subway_.reset();

  EXPECT_EQ(0, subway_.getStationsCount());
  EXPECT_EQ(0, subway_.getTramsCount());
}

/**
Verify whether unsatisfied pre-conditions indeed trigger failures
*/
TEST_F(SubwaySimulationDomainTests, ContractViolations) {
  int negativeValue = -20;

  Station newStation = Station("A", "B", "C", 12);
  Tram newTram = Tram(10, 10, 10, "A");

  vector<string> invalidStrings = {"", ".", " ", "-", "*", "Antwerpen Centraal"};

  std::vector<std::string>::iterator it;

  it = invalidStrings.begin();
  for (it = invalidStrings.begin(); it < invalidStrings.end(); it++) {
    string currentString = *it;
    EXPECT_DEATH(newStation.setName(currentString), "Station name must be valid");
    EXPECT_DEATH(newStation.setPrevious(currentString), "Previous station name must be valid");
    EXPECT_DEATH(newStation.setNext(currentString), "Next station name must be valid");
    EXPECT_DEATH(newTram.setCurrentStation(currentString), "Tram current station must be valid");
    EXPECT_DEATH(newTram.setStartStation(currentString), "Tram start station must be valid");
  }

  // Test negative numbers
  EXPECT_DEATH(newStation.setTrack(negativeValue), "Station track number can't be negative");
  EXPECT_DEATH(newTram.setSpeed(negativeValue), "Tram speed can't be negative");
  EXPECT_DEATH(newTram.setCapacity(negativeValue), "Tram capacity can't be negative");
  EXPECT_DEATH(newTram.setLine(negativeValue), "Tram line can't be negative");
}
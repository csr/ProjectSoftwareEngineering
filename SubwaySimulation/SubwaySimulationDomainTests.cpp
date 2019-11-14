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
#include "Station.h"

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

/**
Tests getter/setter of Station.
*/
TEST_F(SubwaySimulationDomainTests, StationConstructor) {
  string name = "Antwerpen-Centraal", next = "Antwerpen-Berchem", previous = "Roosendaal";
  int track = 23;
  Station station = Station(name, next, previous, track);
  EXPECT_TRUE(station.properlyInitialized());

  // Test getters
  EXPECT_EQ(name, station.getName());
  EXPECT_EQ(next, station.getNext());
  EXPECT_EQ(previous, station.getPrevious());
  EXPECT_EQ(track, station.getTrack());

  string newName = "Milano-Centrale", newNext = "Milano-Garibaldi", newPrevious = "Milano-Cadorna";
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
  string startStation = "Antwerpen-Centraal";
  Tram tram = Tram(line, capacity, speed, startStation);

  // Test getters
  EXPECT_EQ(line, tram.getLine());
  EXPECT_EQ(capacity, tram.getCapacity());
  EXPECT_EQ(speed, tram.getSpeed());
  EXPECT_EQ(startStation, tram.getStartStation());

  int newLine = 11, newCapacity = 304, newSpeed = 40;
  string newStartStation = "Antwerpen-Berchem";

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

  subway_.clear();

  EXPECT_EQ(0, subway_.getStationsCount());
  EXPECT_EQ(0, subway_.getTramsCount());
}

/**
Tests Subway simulation with one step.
*/
TEST_F(SubwaySimulationDomainTests, SubwaySimpleSimulation) {
  int line = 12;
  Station *station1 = new Station("A", "B", "C", line);
  Station *station2 = new Station("B", "C", "A", line);
  Station *station3 = new Station("C", "A", "B", line);
  Tram *tram = new Tram(line, 32, 60, "A");

  subway_.importData({station1, station2, station3}, {tram});

  EXPECT_EQ(tram->getStartStation(), "A");
  EXPECT_EQ(tram->getCurrentStation(), "A");

  ofstream myfile;
  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "B");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "C");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "B");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "A");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "B");
}

TEST_F(SubwaySimulationDomainTests, SubwayMultipleTramsSimulation) {
  int firstLine = 12;
  int secondLine = 32;
  Station *stationA = new Station("A", "B", "C", firstLine);
  Station *stationB = new Station("B", "C", "A", firstLine);
  Station *stationC = new Station("C", "A", "B", firstLine);

  Station *stationD = new Station("D", "E", "G", secondLine);
  Station *stationE = new Station("E", "F", "D", secondLine);
  Station *stationF = new Station("F", "G", "E", secondLine);
  Station *stationG = new Station("G", "H", "F", secondLine);
  Station *stationH = new Station("H", "D", "G", secondLine);

  Tram *tram1 = new Tram(firstLine, 32, 60, "A");
  Tram *tram2 = new Tram(secondLine, 32, 60, "D");

  subway_.importData({stationG, stationC, stationH, stationB, stationD, stationF, stationA, stationE}, {tram1, tram2});

  // Test start station and current station
  EXPECT_EQ(tram1->getStartStation(), "A");
  EXPECT_EQ(tram1->getCurrentStation(), "A");

  EXPECT_EQ(tram2->getStartStation(), "D");
  EXPECT_EQ(tram2->getCurrentStation(), "D");

  ofstream myfile;
  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "B");
  EXPECT_EQ(tram2->getCurrentStation(), "E");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "C");
  EXPECT_EQ(tram2->getCurrentStation(), "F");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "B");
  EXPECT_EQ(tram2->getCurrentStation(), "G");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "A");
  EXPECT_EQ(tram2->getCurrentStation(), "H");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "B");
  EXPECT_EQ(tram2->getCurrentStation(), "G");
}

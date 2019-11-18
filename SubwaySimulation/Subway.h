//============================================================================
// Name        : Subway.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef SubwaySimulation_H
#define SubwaySimulation_H

using namespace std;
#include "Station.h"
#include "Tram.h"
#include <unordered_map>
#include <vector>

class Subway {
 public:

/**
  Constructor for the Subway class. This creates an empty simulation.\n
  @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  @returns Empty Subway.
*/
  Subway();

  bool properlyInitialized();

/**
  Imports stations and trams into the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling importData");
  @note ENSURE(this->getTramsCount() >= 0, "Trams number are negative");
  @note ENSURE(this->getStationsCount() >= 0, "Stations number are negative");

  @param stations Vector of stations.
  @param trams Vector of trams.
*/
  void importData(vector<Station*> stations, vector<Tram*> trams);

/**
  Generates a string representation of the Subway network.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");
  @returns String representation of Subway.
*/
  string toString();

/**
  Computes the Subway simulation for a given number of steps.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  @note REQUIRE(steps > 0, "Number of steps must be greater than zero");
  @note ENSURE(current <= steps, "Subway doesn't halted the simulation when reach n steps");
  @param steps Number of steps to compute.
  @param outputStream Output stream to use for simulation log output.
*/
  void computeAutomaticSimulation(int steps, std::ostream& outputStream);

/**
  Computes the Subway simulation for one step.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  @note ENSURE(tram->getCurrentStation() == nextState, "Tram didn't move from its starting position");
  @param outputStream Output stream to use for simulation log output.
*/
  void moveTramsOnce(std::ostream& outputStream);

/**
  Getter that returns number of stations in the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  @note ENSURE(size >= 0, "Number of stations inside the subway can't negative");
  @returns Number of stations.
*/
  int getStationsCount();

/**
  Getter that returns number of trams in the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  @note ENSURE(size >= 0, "Number of trams inside the subway can't negative");
  @returns Number of trams.
*/
  int getTramsCount();

/**
  Empties the contents of the Subway simulation.
*/
  void clear();

 private:
  Subway * _initCheck; //!use pointer to myself to verify whether I am properly initialized

  vector<Station*> _stationsArray;
  vector<Tram*> _tramsArray;

  unordered_map<string, Station*> _stationsMap;
  unordered_map<int, Tram*> _tramsMap;
};

#endif

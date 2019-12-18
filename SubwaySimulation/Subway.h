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
#include "SubwaySimulationUtils.h"
#include "Tram.h"
#include <map>
#include <vector>

class Subway {
 public:
/**
  Constructor for the Subway class. This creates an empty simulation.
  @note ENSURE(getTramsCount() == 0, "Trams count must be initially zero");
  @note ENSURE(getStationsCount() == 0, "Stations count must be initially zero");
  @note ENSURE(getCurrentTime() == 0, "Current time must be initially zero");
  @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized");
  @returns Empty Subway.
*/
  Subway();

  bool properlyInitialized();

/**
  Getter for a vector of Station of the Subway
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStations");
  @return Array of Station
*/
  vector<Station*> getStations();

/**
  Getter for a vector of Tram of the Subway
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTracks");
  @return Vector of trams
*/
  vector<Tram*> getTrams();

/**
  Getter for current time
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getCurrentTime");
  @return time related to the simulation
*/
  int getCurrentTime();

/**
  Getter that returns number of stations in the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  @return Number of stations.
*/
  int getStationsCount();

/**
  Getter that returns number of trams in the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  @return Number of stations.
*/
  int getTramsCount();

/**
  Imports stations and trams into the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling importData");
  @note ENSURE(this->getTramsCount() >= 0, "Trams count must be zero or positive");
  @note ENSURE(this->getStationsCount() >= 0, "Stations count must be zero or positive");
  @param stations Vector of stations.
  @param trams Vector of trams.
*/
  void importData(vector<Station*> stations, vector<Tram*> trams);

/**
  Empties the contents of the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling reset");
  @note ENSURE(this->getTramsCount() == 0, "Trams array must be cleared");
  @note ENSURE(this->getStationsCount() == 0, "Stations map must be cleared");
*/
  void reset();

/**
  Computes the Subway simulation for a given number of steps.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  @note REQUIRE(ValidIntegerAttribute(steps), "Number of steps must be positive");
  @note ENSURE(getCurrentTime() == steps, "Time must be equal to number of steps");
  @param steps Number of steps to compute.
  @param outputStream Output stream to use for simulation log output.
  @param statsStream Output stream to use for CSV log output.
*/
  void computeAutomaticSimulation(int steps, ostream& outputStream, ostream& statsStream);

 private:
  Subway * _initCheck; //!use pointer to myself to verify whether I am properly initialized

  int _time;
  vector<Station*> _stationsArray;
  vector<Tram*> _tramsArray;

  void moveTramsOnce(ostream &outputStream, ostream &statsStream);
  void incrementTime();
  void resetCurrentTime();
};

#endif

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
#include <unordered_map>
#include <map>
#include <vector>

class Subway {
 public:

/**
  Constructor for the Subway class. This creates an empty simulation.\n
  @note ENSURE(getTramsCount() == 0, "Trams count must be initially zero");
  @note ENSURE(getStationsCount() == 0, "Stations count must be initially zero");
  @note ENSURE(getCurrentTime() == 0, "Current time must be initially zero");
  @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized");
  @returns Empty Subway.
*/
  Subway();

  bool properlyInitialized();

  vector<Station*> getStations();

  vector<Tram*> getTrams();

/**
  Getter that returns number of trams in the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  @note ENSURE(ValidIntegerAttribute(size), "Trams count can't be negative");
  @returns Number of trams.
*/
  int getTramsCount();

  int getCurrentTime();

  /**
  Getter that returns number of stations in the Subway simulation.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  @note ENSURE(ValidIntegerAttribute(size), "Stations count can't be negative");
  @returns Number of stations.
*/
  int getStationsCount();

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
      Empties the contents of the Subway simulation.
      @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling reset");
      @note ENSURE(this->getTramsCount() == 0, "Trams array must be cleared");
      @note ENSURE(this->getStationsCount() == 0, "Stations map must be cleared");
    */
  void reset();

  /**
  Computes the Subway simulation for a given number of steps.
  @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  @note REQUIRE(steps > 0, "Number of steps must be greater than zero");
  @note  ENSURE(getCurrentTime() <= steps, "Compute Automatic Simulation doesn't halt after n steps");
  @param steps Number of steps to compute.
  @param outputStream Output stream to use for simulation log output.
  @param statsStream Output stream to use for CSV log output.
*/
  void computeAutomaticSimulation(int steps, ostream& outputStream, ostream &statsStream);

  /**
    Increment Time in the Subway Simulation.
    @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling incrementTime");
    @note ENSURE(getCurrentTime() == previous + 1, "Time wasn't incremented in incrementTime");
  */
  void moveTramsOnce(ostream &outputStream, ostream &statsStream);

 private:
  Subway * _initCheck; //!use pointer to myself to verify whether I am properly initialized

  vector<Station*> _stationsArray;
  vector<Tram*> _tramsArray;

  unordered_map<string, Station*> _stationsMap;
  map<pairInt, Tram*> _tramsMap;

  int _time;

  void incrementTime();
  void resetCurrentTime();
  void printStatsData(bool isLeaving, Tram *tram, ostream &statsStream);
};

#endif

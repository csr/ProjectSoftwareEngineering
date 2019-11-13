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
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
  Subway();

  bool properlyInitialized();

  /**
\n REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");
*/
  string toString();

  /**
\n REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeSimulation");
*/
  void computeSimulation(int steps);

  /**
\n REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
*/
  int getStationsCount();

  /**
\n REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
*/
  int getTramsCount();

 private:
  Subway * _initCheck; //!use pointer to myself to verify whether I am properly initialized

  vector<Station*> _stationsArray;
  unordered_map<string, Station*> _stationsMap;
  unordered_map<int, Tram*> _trams;
};
#endif

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

class Subway {
 public:
  Subway();
  string toString();
  void addStationsTrams(unordered_map<string, Station> stations, unordered_map<int, Tram> trams);
  void addStation(Station station);
  void addTram(Tram tram);
  void computeSimulation(int steps);
  int getStationsCount();
  int getTramsCount();

 protected:
  unordered_map<string, Station> stations;
  unordered_map<int, Tram> trams;
};
#endif

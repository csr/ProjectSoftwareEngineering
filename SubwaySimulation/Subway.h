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
#include <map>

class Subway {
 public:
  Subway(){}
  string toString();
  void addStation(Station elem);
  void addTram(Tram elem);
  void movingTram();
  void simulation(int time);

 protected:
//  vector<Station> stations;
//  vector<Tram> trams;
  map<string, Station*> stations;
  map<string, Tram*> trams;
};
#endif

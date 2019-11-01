//============================================================================
// Name        : Tram.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This file holds the header for the Tram class.
//============================================================================

#include "Station.h"

class Tram {
 private:
  int capacity;
  int line;
  Station *startStation;
  double speed;

 public:
  Tram(int capacity, int numLine, Station& startStation, double speed);
  std::string toString();

};

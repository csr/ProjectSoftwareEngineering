//============================================================================
// Name        : Station.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This file holds the header for the Station class.
//============================================================================

#pragma once
#include <string>
#include "Station.h"

using namespace std;

class Station {
 private:
  string name;
  int track;
  string previous;
  string next;

 public:
  Station(string name, int track, string previous, string next);
  
  string toString();

};

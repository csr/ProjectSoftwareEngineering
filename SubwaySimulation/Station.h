//============================================================================
// Name        : Station.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This file holds the header for the Station class.
//============================================================================

#pragma once
#include <string>
using namespace std;

class Station {
 private:
  string name;
  int track;
  Station *previous;
  Station *next;

 public:
  Station(string name, int track, Station previous, Station next);
  
  string toString();

};

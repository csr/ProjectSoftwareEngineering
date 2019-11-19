//============================================================================
// Name        : SimulationObject.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <string>

using namespace std;

#ifndef SUBWAYSIMULATION__SIMULATIONOBJECT_H_
#define SUBWAYSIMULATION__SIMULATIONOBJECT_H_

class SimulationObject {
 public:
/**
  Constructs a basic simulation object.
  @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
  SimulationObject();

  bool properlyInitialized();

 protected:
  SimulationObject * _initCheck; //!use pointer to myself to verify whether I am properly initialized

  /**
  Checks if the attribute string is valid.
  @returns True if the string isn't empty.
*/
  bool validStringAttribute(string string);

/**
  Checks if the attribute integer is valid.
  @returns True if the value is positive.
*/
  bool validIntegerAttribute(int value);
};

#endif

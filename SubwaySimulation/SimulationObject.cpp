//============================================================================
// Name        : SimulationObject.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================


#include "SimulationObject.h"
#include "DesignByContract.h"

SimulationObject::SimulationObject() {
  _initCheck = this;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool SimulationObject::properlyInitialized() {
  return _initCheck == this;
}

bool SimulationObject::validIntegerAttribute(int value) {
  return value >= 0;
}

bool SimulationObject::validStringAttribute(string string) {
  return !string.empty();
}
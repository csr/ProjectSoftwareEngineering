//============================================================================
// Name        : SimulationObject.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================


#include "SimulationObject.h"

bool SimulationObject::validIntegerAttribute(int value) {
  return value >= 0;
}

bool SimulationObject::validStringAttribute(string string) {
  return !string.empty();
}
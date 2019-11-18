//============================================================================
// Name        : SimulationObject.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#import <string>

using namespace std;

#ifndef SUBWAYSIMULATION__SIMULATIONOBJECT_H_
#define SUBWAYSIMULATION__SIMULATIONOBJECT_H_

class SimulationObject {
 protected:
  bool validStringAttribute(string string);
  bool validIntegerAttribute(int value);
};

#endif
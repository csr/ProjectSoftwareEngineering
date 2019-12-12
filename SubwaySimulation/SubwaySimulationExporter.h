//
// Created by Marco Natali, Veronica Orsanigo, Cesare de Cal.
//

#ifndef SUBWAYSIMULATION_OUTPUT_H
#define SUBWAYSIMULATION_OUTPUT_H
#include <cstdlib>
#include <string>
#include "Subway.h"

using namespace std;

class SubwaySimulationExporter {
 public:
  void graficalOutput(string fileName, Subway& subway);
  void simpleOutput(string  fileName, Subway& subway);
};

#endif
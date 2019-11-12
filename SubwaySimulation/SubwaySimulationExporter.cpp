//============================================================================
// Name        : SubwaySimulationExporter.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>

#include "SubwaySimulationExporter.h"
#include "DesignByContract.h"

SubwaySimulationExporter::SubwaySimulationExporter(Subway& subway, const char * outputFileName) {
  _initCheck = this;
  ENSURE(properlyInitialized(),
         "constructor must end in properlyInitialized state");
  cout << "Ok, I'm going to export the contents of this subway to output with file name: " << outputFileName << endl;
}

bool SubwaySimulationExporter::properlyInitialized() {
  return _initCheck == this;
}

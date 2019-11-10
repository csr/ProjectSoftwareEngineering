//============================================================================
// Name        : SubwaySimulationExporter.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include "SubwaySimulationExporter.h"
#include "DesignByContract.h"

SubwaySimulationExporter::SubwaySimulationExporter() {
  _initCheck = this;
  ENSURE(properlyInitialized(),
         "constructor must end in properlyInitialized state");
}

bool SubwaySimulationExporter::properlyInitialized() {
  return _initCheck == this;
}

//============================================================================
// Name        : SubwaySimulationExporter.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================


#ifndef SUBWAYSIMULATION__SUBWAYSIMULATIONEXPORTER_H_
#define SUBWAYSIMULATION__SUBWAYSIMULATIONEXPORTER_H_

#include "Subway.h"

enum SuccessEnum {Success, ExportError};

class SubwaySimulationExporter {
 public:
  SubwaySimulationExporter(Subway& subway, const char * outputFileName);
  bool properlyInitialized();

 private:
  SubwaySimulationExporter * _initCheck; //!use pointer to myself to verify whether I am properly initialized
};

#endif //SUBWAYSIMULATION__SUBWAYSIMULATIONEXPORTER_H_

//============================================================================
// Name        : SubwaySimulationExporter.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================


#ifndef SUBWAYSIMULATION__SUBWAYSIMULATIONEXPORTER_H_
#define SUBWAYSIMULATION__SUBWAYSIMULATIONEXPORTER_H_

class SubwaySimulationExporter {
 public:
  SubwaySimulationExporter();
  bool properlyInitialized();

 private:
  SubwaySimulationExporter * _initCheck; //!use pointer to myself to verify whether I am properly initialized
};

#endif //SUBWAYSIMULATION__SUBWAYSIMULATIONEXPORTER_H_

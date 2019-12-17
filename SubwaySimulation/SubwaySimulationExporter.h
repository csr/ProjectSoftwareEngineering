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
  SubwaySimulationExporter(Subway *subway);

  bool properlyInitialized();

  /**
     Generates a string representation of the Subway network.
      @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");
     @returns String representation of Subway.
   */
  string simpleOutput();

  /**
    Generates a graphic string representation of the Subway network.
    @note REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");
    @returns String graphical representation of Subway.
  */
  string graficalOutput();

 private:
  SubwaySimulationExporter * _initCheck; //!use pointer to myself to verify whether I am properly initialized
  Subway* _subway;
};

#endif
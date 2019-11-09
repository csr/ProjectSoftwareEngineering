//============================================================================
// Name        : SubwaySimulationImporter.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#ifndef UNTITLED_SUBWAYSIMULATIONIMPORTER_H
#define UNTITLED_SUBWAYSIMULATIONIMPORTER_H

#include <vector>
#include <map>

#include "tinyxml.h"
#include "Tram.h"
#include "Subway.h"

using namespace std;

enum RootElementType {StationType, TramType, InvalidType};
enum SuccessEnum {Success, PartialImport, ImportAborted};

// Goals: parsing the schedule of the subway network: the different stations, how they are connected to each other,
// and the different trams.

class SubwaySimulationImporter {
 public:
  static SuccessEnum importSubway(const char * inputFileName, std::ostream& errStream, Subway& subway);
};

#endif
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

// Success: import completed with no errors
// SuccessWithInvalidData: import completed with one or more syntax errors
// FailedWithInconsistentData: failed to import due to consistency reasons
// FailedWithInvalidFileName: failed to import due to invalid input file name
enum SuccessEnum {Success, SuccessWithInvalidData, FailedWithInconsistentData, FailedWithInvalidFileName};

// Goals: parsing the schedule of the subway network: the different stations, how they are connected to each other,
// and the different trams.

class SubwaySimulationImporter {
 public:
  static SuccessEnum importSubway(const char * inputFileName, std::ostream& errStream, Subway& subway);
};

#endif
//
// Created by Cesare de Cal on 10/23/19.
//

#ifndef SubwaySimulationImporter_H
#define SubwaySimulationImporter_H

#include <iostream>
#include "Subway.h"

enum SuccessEnum {ImportAborted, PartialImport, Success};

class TicTacToeImporter {
 public:

/**
// Read an XML description of a Subway from inStream and add it to the simulation.
// If errors occur, report them on errStream.
// Return whether successful in the errorcode:
//	- ImportAborted = Subway is unchanged; reason for abortion is reported on errStream
//  - PartialImport = Some semantic errors reported on errStream; state is partially imported and board might have changed
//  - Success = No importer errors; no errors reported
//
*/
  static SuccessEnum importSubwaySimulation(const char * inputfilename, std::ostream& errStream, Subway& subway);
};

// Closing of the ``header guard''.
#endif
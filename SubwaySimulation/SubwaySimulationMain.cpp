//============================================================================
// Name        : SubwaySimulationMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Subway.h"
#include "SubwaySimulationImporter.h"

using namespace std;

int main(int argc, char **argv) {
  cout << "Welcome to the Subway Simulation! Running on release target.\n";
  cout << "Enter file name of the schedule of the subway network: ";

  string inputFileName;
  cin >> inputFileName;

  // Handle file names with or without ending ".xml"?
  cout << "Parsing file with name: " << inputFileName;

  Subway subway;

}

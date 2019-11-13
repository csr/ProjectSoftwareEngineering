//============================================================================
// Name        : SubwaySimulationMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Subway.h"
#include "SubwaySimulationImporter.h"

using namespace std;

int main(int argc, char **argv) {
  cout << "Welcome to the Subway Simulation! Running on release target.\n";

  ofstream errorFile;
  errorFile.open("testInput/userOutput.txt");

  bool shouldKeepAsking = true;

  Subway subway = Subway();

  while (shouldKeepAsking) {
    cout << "Enter file name of the schedule of the subway network (including .xml): ";

    string inputFileName;
    cin >> inputFileName;

    cout << "Parsing file with name: " << inputFileName << endl;
    cout << "Output:" << endl;

    subway.clear();

    SuccessEnum importResult = SubwaySimulationImporter::importSubway(inputFileName.c_str(), errorFile, subway);
    if (importResult == Success) {
      cout << "Import successful." << endl;
    } else {
      cout << "Something went wrong when importing the file." << endl;
    }

    errorFile.close();
  }
}

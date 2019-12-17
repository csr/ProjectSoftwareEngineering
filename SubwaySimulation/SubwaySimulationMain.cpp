//============================================================================
// Name        : SubwaySimulationMain.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

#include "Subway.h"
#include "SubwaySimulationImporter.h"
#include "SubwaySimulationExporter.h"

using namespace std;

string stripXMLExtension(string string) {
  const unsigned long dot = string.rfind(".xml");
  const unsigned long value = std::string::npos;

  if (dot != value) {
    string.resize(dot);
  }
  return string;
}

string getInputFileName() {
  string fileName;
  bool isValid = false;

  while (!isValid) {
    cout << "Enter input file name (should be in userFiles folder): ";

    cin >> fileName;
    std::ifstream infile("userFiles/" + fileName);

    if (!infile.good()) {
      cout << "Input file not found. Try again." << endl;
    }

    isValid = infile.good();
  }

  // Remove .xml extension if any
  return stripXMLExtension(fileName);
}

int getNumberOfSimulationSteps() {
  bool isInputValid = false;
  int steps = 0;

  while (!isInputValid) {
    cout << "Enter number of steps for the simulation to run: ";
    cin >> steps;

    if (steps < 0) {
      cout << "Number of steps needs to be positive. Try again." << endl;
    } else {
      isInputValid = true;
    }
  }
  return steps;
}

void runUserProgram() {
  ofstream errorFile, simpleOutputFile, statsFile, graphicalOutputFile;

  string inputFileName = getInputFileName();
  string errorFileDirectory = "userFiles/temporaryError.txt";

  int steps = getNumberOfSimulationSteps();

  cout << "Importing file with name " << inputFileName << "..." << endl;
  string inputFileNameDirectory = "userFiles/" + inputFileName + ".xml";
  string simulationFileNameDirectory = "userFiles/" + inputFileName + ".txt";
  string statsFileNameDirectory = "userFiles/" + inputFileName + "Stats.csv";
  string graphicalOutputFileNameDirectory = "userFiles/" + inputFileName + "GraphicalOutput.txt";
  statsFile.open(statsFileNameDirectory);
  graphicalOutputFile.open(graphicalOutputFileNameDirectory);

  Subway subway = Subway();
  errorFile.open(errorFileDirectory, std::ofstream::out | std::ofstream::trunc);
  SuccessEnum importResult = SubwaySimulationImporter::importSubway(inputFileNameDirectory.c_str(), errorFile, subway);

  graphicalOutputFile << "Before simulation:" << endl;

  SubwaySimulationExporter exporter = SubwaySimulationExporter(&subway);
  graphicalOutputFile << exporter.graficalOutput() << endl;

  subway.computeAutomaticSimulation(steps, cout, statsFile);

  string simpleOutputFileNameDirectory = "userFiles/" + inputFileName + ".txt";

  if (importResult == Success || importResult == PartialImport) {
    simpleOutputFile.open(simpleOutputFileNameDirectory.c_str());
    simpleOutputFile << exporter.simpleOutput();

    graphicalOutputFile << "After simulation:" << endl;
    graphicalOutputFile << exporter.graficalOutput();
  } else {
    cout << "Couldn't import file. Error printed in " << errorFileDirectory << endl;
  }

  if (importResult == Success) {
    cout << "Import successful. I saved the simple output in " << simpleOutputFileNameDirectory << endl;
    cout << "I've also saved the CSV file in " << statsFileNameDirectory << endl;
  } else if (importResult == PartialImport) {
    cout << "Import semi-successful. I saved the simple output in " << simpleOutputFileNameDirectory << endl;
    cout << "I've also saved the CSV file in " << statsFileNameDirectory << endl;
    cout << "Error(s) printed in " << errorFileDirectory << endl;
  }

  // Make sure we clean our subway simulation environment once we're done printing
  subway.reset();

  simpleOutputFile.close();
  errorFile.close();
}

int main(int argc, char **argv) {
  cout << "Welcome to the Subway Simulation!" << endl;
  bool shouldKeepRunning = true;
  while (shouldKeepRunning) {
    runUserProgram();
  }
}

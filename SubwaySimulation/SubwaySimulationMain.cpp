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

using namespace std;

string stripXMLExtension(string string) {
  // Removed unsigned because otherwise code wouldn't compile - cdecal
  int dot = string.rfind(".xml");
  if (dot != std::string::npos) {
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

    if (steps <= 0) {
      cout << "Number of steps needs to be greater than zero. Try again." << endl;
    } else {
      isInputValid = true;
    }
  }
  return steps;
}

void runUserProgram() {
  ofstream errorFile, simpleOutputFile;

  errorFile.open("userFiles/temporaryError.txt");

  string inputFileName = getInputFileName();
  int steps = getNumberOfSimulationSteps();

  cout << "Importing file with name " << inputFileName << "..." << endl;
  string inputFileNameDirectory = "userFiles/" + inputFileName + ".xml";
  string simulationFileNameDirectory = "userFiles/" + inputFileName + ".txt";

  Subway subway = Subway();
  SuccessEnum importResult = SubwaySimulationImporter::importSubway(inputFileNameDirectory.c_str(), errorFile, subway);

  cout << "Running simulation for " << steps << " steps..." << endl;

  subway.computeAutomaticSimulation(steps, cout);

  if (importResult == Success) {
    string simpleOutputFileNameDirectory = "userFiles/" + inputFileName + ".txt";
    simpleOutputFile.open(simpleOutputFileNameDirectory);
    errorFile.open("userFiles/temporaryError.txt");
    simpleOutputFile << subway.toString();
    cout << "Import successful. I saved the simple output in " << simpleOutputFileNameDirectory << endl;
  } else {
    cout << "Something went wrong when importing the file. Error printed in userFiles/temporaryError." << endl;
  }

  // Make sure we clean our subway simulation environment once we're done printing
  subway.clear();

  errorFile.close();
}

int main(int argc, char **argv) {
  cout << "Welcome to the Subway Simulation!" << endl;
  bool shouldKeepRunning = true;
  while (shouldKeepRunning) {
    runUserProgram();
  }
}

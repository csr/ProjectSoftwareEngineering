//
// Created by Marco Natali, Veronica Orsanigo, Cesare de Cal on 11/12/19.
//

#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>

using namespace std;

#include "Subway.h"
#include "Tram.h"
#include "SubwaySimulationUtils.h"
#include "SubwaySimulationImporter.h"

class SubwaySimulationMovingTests: public ::testing::Test {
 protected:
  friend class Subway;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  Subway subway_;
};

//Tests Subway simulation with one step.
TEST_F(SubwaySimulationMovingTests, SubwayAutomaticSimulation) {
  ASSERT_TRUE(DirectoryExists("testInput"));
  ASSERT_TRUE(DirectoryExists("testSimulation"));

  ofstream errorFile;
  ofstream statsFile;
  ofstream temporaryOutputFile;

  SuccessEnum importResult;

  int fileCounter = 1;
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
  while (FileExists(fileName)) {
    string temporaryOutputFileName = "testSimulation/temporaryOutput.txt";
    temporaryOutputFile.open(temporaryOutputFileName);
    errorFile.open("testSimulation/errorFile.txt");
    statsFile.open("testSimulation/temporaryStats.txt");

    if (!temporaryOutputFile || !errorFile || !statsFile) {
      cerr << "Unable to open temporaryOutputFile, errorFile or statsFile" << endl;
    }

    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), errorFile, subway_);
    EXPECT_TRUE(importResult == Success);
    subway_.computeAutomaticSimulation(5000, temporaryOutputFile, statsFile);

    string expectedOutputFileName = "testSimulation/expectedSimulationOutput" + ToString(fileCounter) + ".txt";
    EXPECT_TRUE(FileCompare(temporaryOutputFileName, expectedOutputFileName));

    fileCounter++;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

    temporaryOutputFile.close();
    errorFile.close();
    statsFile.close();

    if (temporaryOutputFile.fail()) {
      cerr << "FAILED" << endl;
    }
  }

  EXPECT_TRUE(fileCounter == 5);
}

TEST_F(SubwaySimulationMovingTests, SubwayCSVSimulation) {
  ASSERT_TRUE(DirectoryExists("testInput"));
  ASSERT_TRUE(DirectoryExists("testCSV"));

  ofstream errorFile;
  ofstream statsFile;
  ofstream outputFile;
  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

  string temporaryStatsName = "testCSV/temporaryOutput.csv";

  while (fileCounter < 5) {
    errorFile.open("testCSV/errorFile.txt");
    statsFile.open(temporaryStatsName);

    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputFile, subway_);
    EXPECT_TRUE((importResult == Success));

    subway_.computeAutomaticSimulation(5000, outputFile, statsFile);

    string expectedOutputFileName = "testCSV/expectedCSVOutput" + ToString(fileCounter) + ".csv";
    EXPECT_TRUE(FileCompare(temporaryStatsName, expectedOutputFileName));

    fileCounter = fileCounter + 1;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
  };
  EXPECT_TRUE(fileCounter == 5);
}

/*
TEST_F(SubwaySimulationMovingTests, SubwayCollisionSimulation) {
}
TEST_F(SubwaySimulationMovingTests, SubwayPassengersSimulation) {}

TEST_F(SubwaySimulationMovingTests, SubwayTurnoverSimulation) {
}
*/
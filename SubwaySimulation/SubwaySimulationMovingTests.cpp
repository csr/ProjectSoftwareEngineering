//
// Created by Marco Natali, Veronica Orsanigo, Cesare de Cal on 11/12/19.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "Subway.h"
#include "Tram.h"
#include "SubwaySimulationUtils.h"
#include "SubwaySimulationImporter.h"
#include "SubwaySimulationExporter.h"

class SubwaySimulationMovingTests: public ::testing::Test {
 protected:
  friend class Subway;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  Subway subway_;
};



  TEST_F(SubwaySimulationMovingTests, MovingTram) {
  //if directory doesn't exist then no need in proceeding with the test
  ASSERT_TRUE(DirectoryExists("testInput"));
  ASSERT_TRUE(DirectoryExists("testSimulation"));
 
  ofstream outputContainerFile;
  SuccessEnum importResult;
  int fileCounter = 1; 
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

  while (FileExists(fileName)) {
    string temporaryOutput = "testSimulation/temporaryOutput.txt";
    outputContainerFile.open(temporaryOutput);

    // The outputContainerFile will be passed as the "error" file to the import subway
    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

    EXPECT_TRUE(importResult == Success);

    subway_.moveTramsOnce(outputContainerFile);
    outputContainerFile.close();

    string expectedOutputFilename = "testSimulation/legalSubwayMoving" + ToString(fileCounter) + ".txt";
    EXPECT_TRUE(FileCompare("testSimulation/temporaryOutput.txt", expectedOutputFilename));

    fileCounter = fileCounter + 1;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
   }  
}

TEST_F(SubwaySimulationMovingTests, AutomaticSimulation) {
  //if directory doesn't exist then no need in proceeding with the test
  ASSERT_TRUE(DirectoryExists("testInput"));
  ASSERT_TRUE(DirectoryExists("testSimulation"));

  ofstream outputContainerFile;

  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

  while (FileExists(fileName)) {
    string temporaryOutput = "testSimulation/temporaryOutput.txt";
    outputContainerFile.open(temporaryOutput);

    // The outputContainerFile will be passed as the "error" file to the import subway
    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

    EXPECT_TRUE(importResult == Success);

    // The outputContainerFile will also be used to dump the contents of subway_.toString()
    subway_.computeAutomaticSimulation(6, outputContainerFile);
    outputContainerFile.close();

    string expectedOutputFilename = "testSimulation/legalSubwaySimulation" + ToString(fileCounter) + ".txt";
    EXPECT_TRUE(FileCompare(temporaryOutput, expectedOutputFilename));

    fileCounter = fileCounter + 1;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
  };
}


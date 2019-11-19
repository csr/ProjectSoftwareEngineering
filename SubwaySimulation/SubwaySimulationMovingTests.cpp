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

/**
Tests Subway simulation with one step.
*/
TEST_F(SubwaySimulationMovingTests, SubwaySimpleSimulation) {
  int line = 12;
  Station *station1 = new Station("A", "B", "C", line);
  Station *station2 = new Station("B", "C", "A", line);
  Station *station3 = new Station("C", "A", "B", line);
  Tram *tram = new Tram(line, 32, 60, "A");

  subway_.importData({station1, station2, station3}, {tram});

  EXPECT_EQ(tram->getStartStation(), "A");
  EXPECT_EQ(tram->getCurrentStation(), "A");

  ofstream myfile;
  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "B");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "C");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "B");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "A");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram->getCurrentStation(), "B");
}

TEST_F(SubwaySimulationMovingTests, SubwayMultipleTramsSimulation) {
  int firstLine = 12;
  int secondLine = 32;
  Station *stationA = new Station("A", "B", "C", firstLine);
  Station *stationB = new Station("B", "C", "A", firstLine);
  Station *stationC = new Station("C", "A", "B", firstLine);

  Station *stationD = new Station("D", "E", "G", secondLine);
  Station *stationE = new Station("E", "F", "D", secondLine);
  Station *stationF = new Station("F", "G", "E", secondLine);
  Station *stationG = new Station("G", "H", "F", secondLine);
  Station *stationH = new Station("H", "D", "G", secondLine);

  Tram *tram1 = new Tram(firstLine, 32, 60, "A");
  Tram *tram2 = new Tram(secondLine, 32, 60, "D");

  subway_.importData({stationG, stationC, stationH, stationB, stationD, stationF, stationA, stationE}, {tram1, tram2});

  // Test start station and current station
  EXPECT_EQ(tram1->getStartStation(), "A");
  EXPECT_EQ(tram1->getCurrentStation(), "A");

  EXPECT_EQ(tram2->getStartStation(), "D");
  EXPECT_EQ(tram2->getCurrentStation(), "D");

  ofstream myfile;
  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "B");
  EXPECT_EQ(tram2->getCurrentStation(), "E");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "C");
  EXPECT_EQ(tram2->getCurrentStation(), "F");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "B");
  EXPECT_EQ(tram2->getCurrentStation(), "G");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "A");
  EXPECT_EQ(tram2->getCurrentStation(), "H");

  subway_.moveTramsOnce(myfile);
  EXPECT_EQ(tram1->getCurrentStation(), "B");
  EXPECT_EQ(tram2->getCurrentStation(), "G");
}
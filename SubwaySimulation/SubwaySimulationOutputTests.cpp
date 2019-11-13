//
// Created by Cesare de Cal on 11/12/19.
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

class SubwaySimulationOutputTests: public ::testing::Test {
 protected:
  friend class Subway;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  Subway subway_;
};

TEST_F(SubwaySimulationOutputTests, ExampleOutputTest) {
  //if directory doesn't exist then no need in proceeding with the test
  ASSERT_TRUE(DirectoryExists("testOutput"));

  Station *stationA = new Station("A", "B", "C", 12);
  Station *stationB = new Station("B", "C", "A", 12);
  Station *stationC = new Station("C", "A", "B", 12);

  Tram *tram = new Tram(12, 32, 60, "A");

  subway_.importData({stationA, stationB, stationC}, {tram});
  ASSERT_TRUE(subway_.getStationsCount() == 3);
  ASSERT_TRUE(subway_.getTramsCount() == 1);

  ofstream myfile;
  myfile.open("testOutput/temporaryOutput.txt");
  myfile << subway_.toString();
  myfile.close();
  EXPECT_TRUE(FileCompare("testOutput/temporaryOutput.txt", "testOutput/legalSubwayOutputManual1.txt"));
}


TEST_F(SubwaySimulationOutputTests, LegalSubwaysOutput) {
  //if directory doesn't exist then no need in proceeding with the test
  ASSERT_TRUE(DirectoryExists("testInput"));
  ASSERT_TRUE(DirectoryExists("testOutput"));

  ofstream outputContainerFile;

  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

  while (FileExists(fileName)) {
    string temporaryOutput = "testOutput/temporaryOutput.txt";
    outputContainerFile.open(temporaryOutput);

    // The outputContainerFile will be passed as the "error" file to the import subway
    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

    EXPECT_TRUE(importResult == Success);

    // The outputContainerFile will also be used to dump the contents of subway_.toString()
    outputContainerFile << subway_.toString();
    outputContainerFile.close();

    string expectedOutputFilename = "testOutput/legalSubwayOutput" + ToString(fileCounter) + ".txt";
    EXPECT_TRUE(FileCompare("testOutput/temporaryOutput.txt", expectedOutputFilename));

    fileCounter = fileCounter + 1;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
  };
}
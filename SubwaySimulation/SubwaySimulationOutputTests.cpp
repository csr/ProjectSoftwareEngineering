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
  Subway subway_;
};

TEST_F(SubwaySimulationOutputTests, LegalSubwaysOutput) {
  //if directory doesn't exist then no need in proceeding with the test
  ASSERT_TRUE(DirectoryExists("testInput"));
  ASSERT_TRUE(DirectoryExists("testOutput"));

  ofstream outputContainerFile;

  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

  while (FileExists(fileName)) {
//    cout << "Parsing legal subway with name: " << fileName << endl;
    string temporaryOutput = "testOutput/temporaryOutput.txt";
    outputContainerFile.open(temporaryOutput);

    // The outputContainerFile will be passed as the "error" file to the import subway
    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)

    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

    EXPECT_TRUE(importResult == Success);

    SubwaySimulationExporter exporter = SubwaySimulationExporter(&subway_);

    outputContainerFile << exporter.simpleOutput();
    outputContainerFile.close();

    string expectedOutputFilename = "testOutput/legalSubwayOutput" + ToString(fileCounter) + ".txt";
    EXPECT_TRUE(FileCompare("testOutput/temporaryOutput.txt", expectedOutputFilename));

    fileCounter = fileCounter + 1;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
  };
  EXPECT_TRUE(fileCounter == 5);
}

TEST_F(SubwaySimulationOutputTests, GraphicalOutput) {
   //if directory doesn't exist then no need in proceeding with the test
  ASSERT_TRUE(DirectoryExists("testInput"));
  ASSERT_TRUE(DirectoryExists("testGraphicalOutput"));

  ofstream outputContainerFile;

  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

  while (FileExists(fileName)) {
    string expectedOutputFilename = "testGraphicalOutput/expectedOutput" + ToString(fileCounter) + ".txt";

    string temporaryOutputFileName = "testGraphicalOutput/temporaryOutput.txt";
    outputContainerFile.open(temporaryOutputFileName);

    // The outputContainerFile will be passed as the "error" file to the import subway
    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

    EXPECT_TRUE(importResult == Success);

    SubwaySimulationExporter exporter = SubwaySimulationExporter(&subway_);
    outputContainerFile << exporter.graficalOutput();

    outputContainerFile.close();

    EXPECT_TRUE(FileCompare(expectedOutputFilename, temporaryOutputFileName));

    fileCounter = fileCounter + 1;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
  };
  EXPECT_TRUE(fileCounter == 5);
}
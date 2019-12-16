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
  EXPECT_TRUE(fileCounter == 5);
}
/*
TEST_F(SubwaySimulationOutputTests, GraphicalOutput){
    //if directory doesn't exist then no need in proceeding with the test
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testOutput"));

    ofstream statsFile;
    ofstream outputFile;


    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

    while (FileExists(fileName)) {
        string temporaryOutput = "testOutput/temporaryOutput.txt";

        statsFile.open("testCSV/temporaryOutput.txt");
        outputFile.open("testSimulation/temporaryOutput.txt");

        // The outputContainerFile will be passed as the "error" file to the import subway
        // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputFile, subway_);

        EXPECT_TRUE(importResult == Success);

        // The outputContainerFile will also be used to dump the contents of subway_.toString()

        subway_.computeAutomaticSimulation(5000, outputFile, statsFile, temporaryOutput);
        statsFile.close();
        outputFile.close();

        string expectedOutputFilename = "testOutput/legalSubwayOutput" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare(temporaryOutput, expectedOutputFilename));

        fileCounter = fileCounter + 1;
        fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    };
    EXPECT_TRUE(fileCounter == 5);

}
//TEST_F(SubwaySimulationOutputTests, PartialSubwaysOutput) {
//  //if directory doesn't exist then no need in proceeding with the test
//  ASSERT_TRUE(DirectoryExists("testInput"));
//  ASSERT_TRUE(DirectoryExists("testOutput"));
//
//  ofstream outputContainerFile;
//  ofstream errorFile;
//
//  SuccessEnum importResult;
//  int fileCounter = 1;
//  string fileName = "testInput/partialSubway" + ToString(fileCounter) + ".xml";
//
//  while (FileExists(fileName)) {
//    string expectedOutputFile = "testInput/partialSubwayOutput" + ToString(fileCounter) + ".xml";
//    outputContainerFile.open("testOutput/temporaryOutput.txt");
//    errorFile.open("testOutput/zzzError.txt");
//
//    // The outputContainerFile will be passed as the "error" file to the import subway
//    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
//    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), errorFile, subway_);
//
//    EXPECT_TRUE(importResult == PartialImport);
//
//    // The outputContainerFile will also be used to dump the contents of subway_.toString()
//    outputContainerFile << subway_.toString();
//    outputContainerFile.close();
//    errorFile.close();
//
//    string expectedOutputFilename = "testOutput/partialSubwayOutput" + ToString(fileCounter) + ".txt";
//    EXPECT_TRUE(FileCompare(expectedOutputFilename, "testOutput/temporaryOutput.txt"));
//
//    fileCounter = fileCounter + 1;
//    fileName = "testInput/partialSubway" + ToString(fileCounter) + ".xml";
//  };
//
//  EXPECT_TRUE(fileCounter == 3);
//}
*/
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

//TEST_F(SubwaySimulationMovingTests, MovingTram) {
//////if directory doesn't exist then no need in proceeding with the test
//  ASSERT_TRUE(DirectoryExists("testInput"));
//  ASSERT_TRUE(DirectoryExists("testSimulation"));
//
//  ofstream outputFile;
//  ofstream statsFile("testCSV/temporaryOutput1.txt");
//  SuccessEnum importResult;
//  int fileCounter = 1;
//  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
//  while(FileExists(fileName)){
//    string temporaryOutputFileName = "testSimulation/temporaryOutput" + ToString(fileCounter) + ".txt";
//    outputFile.open(temporaryOutputFileName);
//
//    // The outputContainerFile will be passed as the "error" file to the import subway
//    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
//    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputFile, subway_);
//
//    EXPECT_TRUE(importResult == Success);
//    vector<string> previous;
//    for(auto elem : subway_.getTrams()){
//      previous.push_back(elem->getCurrentStation()->getName());
//    }
//    subway_.computeAutomaticSimulation(1, outputFile, statsFile);
//    outputFile.close();
//
//    int index = 0;
//    for(auto elem : subway_.getTrams()){
//      EXPECT_TRUE(elem->getCurrentStation()->getName() == previous[index]);
//      index++;
//    }
//
//    fileCounter = fileCounter + 1;
//    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
//  }
//
//  EXPECT_TRUE(fileCounter == 5);
//}
//


//Tests Subway simulation with one step.
TEST_F(SubwaySimulationMovingTests, SubwaySimpleAutomaticSimulation) {
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

//  EXPECT_TRUE(fileCounter == 5);
}
/*
TEST_F(SubwaySimulationMovingTests, SubwayNormalAutomaticSimulation) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testSimulation"));

    ofstream outputContainerFile;

    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    string temporaryOutput = "testSimulation/temporaryOutput.txt";

    //while (FileExists(fileName)) {
        outputContainerFile.open(temporaryOutput);
        // The outputContainerFile will be passed as the "error" file to the import subway
        // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

        EXPECT_TRUE(importResult == Success);

        // The outputContainerFile will also be used to dump the contents of subway_.toString()
        subway_.computeAutomaticSimulation(1000, outputContainerFile, statsFile);
        outputContainerFile.close();

        string expectedOutputFilename = "testSimulation/normal/legalSubwaySimulation" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare(temporaryOutput, expectedOutputFilename));
        fileCounter++;
        fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
        cout << "Done it" << endl;
    //}
    //EXPECT_TRUE(fileCounter == 5);
}

TEST_F(SubwaySimulationMovingTests, SubwayComplexAutomaticSimulation) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testSimulation"));

    ofstream outputContainerFile;

    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    string temporaryOutput = "testSimulation/temporaryOutput1txt";

    while (FileExists(fileName)) {
        outputContainerFile.open(temporaryOutput);
        // The outputContainerFile will be passed as the "error" file to the import subway
        // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

        EXPECT_TRUE(importResult == Success);

        // The outputContainerFile will also be used to dump the contents of subway_.toString()
        subway_.computeAutomaticSimulation(2000, outputContainerFile);
        outputContainerFile.close();

        string expectedOutputFilename = "testSimulation/complex/legalSubwaySimulation" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare(temporaryOutput, expectedOutputFilename));
        fileCounter++;
        fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
        cout << "Done it" << endl;
    }
    EXPECT_TRUE(fileCounter == 5);
}
TEST_F(SubwaySimulationMovingTests, SubwayCollisionSimulation){
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testSimulation"));

    ofstream outputFile;
    SuccessEnum importResult;

    int fileCounter = 1;
    string fileName = "testInput/collisionSubway" + ToString(fileCounter) + ".xml";
    string temporaryOutput = "testSimulation/temporaryOutput.txt";

    while(FileExists(fileName)) {
        outputFile.open(temporaryOutput);

        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputFile, subway_);

        EXPECT_TRUE(importResult == Success);
        subway_.computeAutomaticSimulation(1, outputFile);
        outputFile.close();

        string expectedOutputFilename = "testSimulation/collisionSimulation" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare(temporaryOutput, expectedOutputFilename));
        fileCounter++;
        fileName = "testInput/collisionSubway" + ToString(fileCounter) + ".xml";
    }
    EXPECT_TRUE(fileCounter == 5);

}

TEST_F(SubwaySimulationMovingTests, SubwayPassengersSimulation) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testSimulation"));

    ofstream outputFile;
    SuccessEnum importResult;

    int fileCounter = 1;
    string fileName = "testInput/collisionSubway" + ToString(fileCounter) + ".xml";
    string temporaryOutput = "testSimulation/temporaryOutput.txt";

    while(FileExists(fileName)) {
        outputFile.open(temporaryOutput);

        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputFile, subway_);

        EXPECT_TRUE(importResult == Success);
        subway_.computeAutomaticSimulation(500, outputFile);
        outputFile.close();

        string expectedOutputFilename = "testSimulation/collisionSimulation" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare(temporaryOutput, expectedOutputFilename));
        fileCounter++;
        fileName = "testInput/collisionSubway" + ToString(fileCounter) + ".xml";
    }
    EXPECT_TRUE(fileCounter == 5);
}
*/
/*
TEST_F(SubwaySimulationMovingTests, SubwayTurnoverSimulation) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testSimulation"));

    ofstream outputFile;
    SuccessEnum importResult;

    int fileCounter = 1;
    string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    string temporaryOutput = "testSimulation/temporaryOutput.txt";

    while(FileExists(fileName)) {
        outputFile.open(temporaryOutput);

        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputFile, subway_);

        EXPECT_TRUE(importResult == Success);
        subway_.computeAutomaticSimulation(1, outputFile);
        outputFile.close();

        fileCounter++;
        fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    }
    EXPECT_TRUE(fileCounter == 5);
}
*/
//TEST_F(SubwaySimulationMovingTests, SubwayCSVSimulation) {
//  ASSERT_TRUE(DirectoryExists("testInput"));
//  ASSERT_TRUE(DirectoryExists("testCSV"));
//
//  ofstream myfile;
//  ofstream statsFile;
//  ofstream outputStream("testSimulation/temporaryOutput.txt");
//  SuccessEnum importResult;
//  int fileCounter = 1;
//  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
//  statsFile.open("testCSV/temporaryOutput.txt");
//
//  while (FileExists (fileName)) {
//    cout << "Parsing file name: " << fileName << endl;
//    myfile.open("testInput/zzzError.txt");
//    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), myfile, subway_);
//    myfile.close();
//    EXPECT_TRUE((importResult == Success));
//
//    subway_.computeAutomaticSimulation(5000, outputStream, statsFile);
//
//    statsFile << "Hey there!" << endl;
//
//    fileCounter = fileCounter + 1;
//    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
//  };
//  EXPECT_TRUE(fileCounter == 5);
//}

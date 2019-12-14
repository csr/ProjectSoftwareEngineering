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

TEST_F(SubwaySimulationMovingTests, MovingTram) {
////if directory doesn't exist then no need in proceeding with the test
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testSimulation"));

    ofstream outputFile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    while(FileExists(fileName)){
        string temporaryOutput = "testSimulation/temporaryOutput.txt";
        outputFile.open(temporaryOutput);

    // The outputContainerFile will be passed as the "error" file to the import subway
    // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputFile, subway_);

        EXPECT_TRUE(importResult == Success);

        vector<string> previous;
        for(auto elem : subway_.getTrams()){
            previous.push_back(elem->getCurrentStation()->getName());
        }
        subway_.moveTramsOnce(outputFile);
        outputFile.close();

        int index = 0;
        for(auto elem : subway_.getTrams()){
            EXPECT_TRUE(elem->getCurrentStation()->getName() == previous[index]);
            index++;
        }

        fileCounter = fileCounter + 1;
        fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    }

    EXPECT_TRUE(fileCounter == 5);
}
//


//Tests Subway simulation with one step.
//
TEST_F(SubwaySimulationMovingTests, SubwaySimpleAutomaticSimulation) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(DirectoryExists("testSimulation"));

    ofstream outputContainerFile;

    SuccessEnum importResult;
    int fileCounter = 3;
    string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
    string temporaryOutput = "testSimulation/temporaryOutput.txt";

    while (FileExists(fileName)) {
        outputContainerFile.open(temporaryOutput);
        // The outputContainerFile will be passed as the "error" file to the import subway
        // If the import result is Success, there should be NO error output (an empty error file means everything was ok)
        importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), outputContainerFile, subway_);

        EXPECT_TRUE(importResult == Success);

        // The outputContainerFile will also be used to dump the contents of subway_.toString()
        subway_.computeAutomaticSimulation(500, outputContainerFile);
        outputContainerFile.close();

        string expectedOutputFilename = "testSimulation/simple/legalSubwaySimulation" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare(temporaryOutput, expectedOutputFilename));
        fileCounter++;
        fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
        cout << "Done it" << endl;
    }
    EXPECT_TRUE(fileCounter == 5);
}

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
        subway_.computeAutomaticSimulation(1000, outputContainerFile);
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
    string temporaryOutput = "testSimulation/temporaryOutput.txt";

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

TEST_F(SubwaySimulationMovingTests, SubwayPassengersSimulation){
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

TEST_F(SubwaySimulationMovingTests, SubwayTurnoverSimulation){
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
        subway_.moveTramsOnce(outputFile);
        outputFile.close();

        EXPECT_TRUE(00);
        fileCounter++;
        fileName = "testInput/collisionSubway" + ToString(fileCounter) + ".xml";
    }
    EXPECT_TRUE(fileCounter == 5);
}

TEST_F(SubwaySimulationMovingTests, SubwayCSVSimulation){

}

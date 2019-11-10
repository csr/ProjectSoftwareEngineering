//============================================================================
// Name        : SubwaySimulationInputTests.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "Subway.h"
#include "SubwaySimulationUtils.h"
#include "SubwaySimulationImporter.h"

class SubwaySimulationInputTests: public ::testing::Test {
 protected:
  friend class Subway;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  Subway subway_;
};

TEST_F(SubwaySimulationInputTests, InputLegalSubways) {
  ASSERT_TRUE(DirectoryExists("testInput"));

  ofstream myfile;
  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";

  while (FileExists (fileName)) {
    myfile.open("testInput/zzzError.txt");
    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), myfile, subway_);
    myfile.close();
    EXPECT_TRUE((importResult == Success) || (importResult == PartialImport));
    EXPECT_TRUE(FileIsEmpty("testInput/zzzError.txt"));

    fileCounter = fileCounter + 1;
    fileName = "testInput/legalSubway" + ToString(fileCounter) + ".xml";
  };
}

TEST_F(SubwaySimulationInputTests, InputXMLSyntaxErrors) {
  ASSERT_TRUE(DirectoryExists("testInput"));

  ofstream myfile;
  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/xmlsyntaxerror" + ToString(fileCounter) + ".xml";
  string errorfileName;

  while (FileExists(fileName)) {

    myfile.open( "testInput/zzzError.txt");
    myfile << "Helllo";

    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), myfile, subway_);
    myfile.close();
    EXPECT_TRUE(importResult == ImportAborted);
    errorfileName = "testInput/xmlsyntaxerror" + ToString(fileCounter) + ".txt";
    EXPECT_TRUE(FileCompare("testInput/zzzError.txt", errorfileName));

    fileCounter = fileCounter + 1;
    fileName = "testInput/xmlsyntaxerror" + ToString(fileCounter) + ".xml";
  };
//  EXPECT_TRUE(fileCounter == 3);
}

TEST_F(SubwaySimulationInputTests, InputIllegalSimulations) {
  ASSERT_TRUE(DirectoryExists("testInput"));

  ofstream myfile;
  SuccessEnum importResult;
  int fileCounter = 1;
  string fileName = "testInput/illegalSubway" + ToString(fileCounter) + ".xml";
  string errorfileName;

  while (FileExists (fileName)) {
    myfile.open("testInput/zzzError.txt");
    importResult = SubwaySimulationImporter::importSubway(fileName.c_str(), myfile, subway_);
    myfile.close();
    EXPECT_TRUE(importResult == PartialImport);
    errorfileName = "testInput/illegalError" + ToString(fileCounter) + ".txt";
    EXPECT_TRUE(FileCompare("testInput/zzzError.txt", errorfileName));

    fileCounter = fileCounter + 1;
    fileName = "testInput/illegalSubway" + ToString(fileCounter) + ".xml";
  };
//	EXPECT_TRUE(fileCounter == 6);
}

/**
Tests import of a file with an invalid root.
*/
TEST_F(SubwaySimulationInputTests, ImportWithInvalidRoot) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/invalidRoot.xml", myfile, subway_);
  EXPECT_TRUE(importResult == PartialImport);
}

/**
Tests import of file with a station missing its name.
*/
TEST_F(SubwaySimulationInputTests, ImportWithInvalidStation) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/invalidStationMissingName.xml", myfile, subway_);
  EXPECT_TRUE(importResult == PartialImport);
}

/**
Tests import of a station with an invalid track.
*/
TEST_F(SubwaySimulationInputTests, ImportStationWithInvalidTrack) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/invalidStationTrack.xml", myfile, subway_);
  EXPECT_TRUE(importResult == PartialImport);
}

/**
Tests import of an empty file.
*/
TEST_F(SubwaySimulationInputTests, ImportEmptyFile) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/empty.xml", myfile, subway_);
  EXPECT_TRUE(importResult == Success);
}

/**
Tests strings of stations and trams (must not contain numbers, whitespaces or special characters).
*/
TEST_F(SubwaySimulationInputTests, ImportStationTramWithInvalidStrings) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/invalidStationTramStrings.xml", myfile, subway_);
  EXPECT_TRUE(importResult == PartialImport);
}

/**
Tests a file containing a station with a duplicate tag.
*/
TEST_F(SubwaySimulationInputTests, ImportStationWithDuplicateTags) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/invalidStationWithDuplicateTags.xml", myfile, subway_);
  EXPECT_TRUE(importResult == PartialImport);
}

/**
Tests a file containing a valid station.
*/
TEST_F(SubwaySimulationInputTests, ImportValidStation) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/legalSubway1.xml", myfile, subway_);
  EXPECT_TRUE(importResult == Success);
}

/**
Tests a file containing a valid tram.
*/
TEST_F(SubwaySimulationInputTests, ImportValidTram) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/legalSubway2.xml", myfile, subway_);
  EXPECT_TRUE(importResult == Success);
}

/**
Tests a file containing a station with a whitespace in its name.
*/
TEST_F(SubwaySimulationInputTests, ImportInvalidStationWithWhitespace) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/invalidStationWithWhitespace.xml", myfile, subway_);
  EXPECT_TRUE(importResult == PartialImport);
}

/**
Tests a file containing a station with a whitespace in its name.
*/
TEST_F(SubwaySimulationInputTests, ImportExample) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/example.xml", myfile, subway_);
  EXPECT_TRUE(importResult == Success);
}
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

  Subway ttt_;
};

/**
Tests testInput folder exists in project.
*/
TEST_F(SubwaySimulationInputTests, InputDirectoryExists) {
  ASSERT_TRUE(DirectoryExists("testInput"));
}

/**
Tests if example XML file given by Professor exists in project.
*/
TEST_F(SubwaySimulationInputTests, ExampleFileExists) {
  ASSERT_TRUE(DirectoryExists("testInput/example.xml"));
}

/**
Tests import of example file given by Professor.
*/
TEST_F(SubwaySimulationInputTests, BasicImport) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("testInput/example.xml", myfile, ttt_);
  EXPECT_TRUE(importResult == Success);
}

/**
Tests import of a file with an invalid root.
*/
TEST_F(SubwaySimulationInputTests, ImportWithInvalidStation) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("../testInput/invalidRoot.xml", myfile, ttt_);
  EXPECT_TRUE(importResult == SuccessWithInvalidData);
}

/**
Tests import of file with invalid station.
*/
TEST_F(SubwaySimulationInputTests, ImportWithInvalidRoot) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("../testInput/invalidStation.xml", myfile, ttt_);
  EXPECT_TRUE(importResult == SuccessWithInvalidData);
}

/**
Tests import of an empty file.
*/
TEST_F(SubwaySimulationInputTests, ImportEmptyFile) {
  ofstream myfile;
  SuccessEnum importResult;
  importResult = SubwaySimulationImporter::importSubway("../testInput/empty.xml", myfile, ttt_);
  EXPECT_TRUE(importResult == Success);
}
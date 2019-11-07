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
Tests Input From File given by Professor
*/
TEST_F(SubwaySimulationInputTests, BasicImport) {
  ASSERT_TRUE(DirectoryExists("testInput"));

  ofstream myfile;
  SuccessEnum importResult;

  myfile.open("testInput/example.xml");
  importResult = SubwaySimulationImporter::importSubway("testInput/example.xml", myfile, ttt_);
  myfile.close();
  cout << "Import Result" << importResult;

  EXPECT_TRUE(importResult != InvalidFileName);
}

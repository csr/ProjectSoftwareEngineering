//============================================================================
// Name        : SubwaySimulationInputTests.h
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
//#include "TicTacToeUtils.h"
#include "SubwaySimulationImporter.h"

#ifndef SUBWAYSIMULATION__SUBWAYSIMULATIONINPUTTESTS_H_
#define SUBWAYSIMULATION__SUBWAYSIMULATIONINPUTTESTS_H_

class SubwaySimulationInputTests: public ::testing::Test {
 protected:
  friend class Subway;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  Subway ttt_;
};

#endif //SUBWAYSIMULATION__SUBWAYSIMULATIONINPUTTESTS_H_

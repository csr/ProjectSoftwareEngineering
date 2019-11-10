//============================================================================
// Name        : SubwaySimulationDomainTests.cpp
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

class SubwaySimulationDomainTest: public ::testing::Test {
 protected:
  friend class Subway;
  // You should make the members protected s.t. they can be
  // accessed from sub-classes.
  // Guardiamo il progetto del prof per capire cosa inserire qui
};
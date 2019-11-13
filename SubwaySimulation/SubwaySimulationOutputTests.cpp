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

  Station stationA = Station("A", "B", "C", 12);
  Station stationB = Station("B", "C", "A", 12);
  Station stationC = Station("C", "A", "B", 12);

  Tram tram = Tram(12, 32, 60, "A");

//  vector<Station*> stations = {stationA, stationB, stationC};
//  subway_.addStations(stations);

//  SubwaySimulationExporter exporter = SubwaySimulationExporter(subway_, "testOutput/hello.txt");
//  exporter.export();

//  ttt_.setMoves("a1c1b2a3c3", "b1a2c2b3");
//
//  ofstream myfile;
//  myfile.open("testOutput/happyDayOut.txt");
//  while (ttt_.notDone()) {
//    ttt_.doMove();
//    ttt_.writeOn(myfile);
//  };
//  myfile.close();
//  EXPECT_TRUE(
//      FileCompare("testOutput/happyDayExpectedOut.txt", "testOutput/happyDayOut.txt"));
}



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

  Station *stationA = new Station("A", "B", "C", 12);
  Station *stationB = new Station("B", "C", "A", 12);
  Station *stationC = new Station("C", "A", "B", 12);

  Tram *tram = new Tram(12, 32, 60, "A");

  subway_.importData({stationA, stationB, stationC}, {tram});
  ASSERT_TRUE(subway_.getStationsCount() == 3);
  ASSERT_TRUE(subway_.getTramsCount() == 1);

  ofstream myfile;
  myfile.open("testOutput/temporaryOutput.txt");
  myfile << subway_.toString();
  myfile.close();
  EXPECT_TRUE(FileCompare("testOutput/temporaryOutput.txt", "testOutput/expectedOutput1.txt"));
}



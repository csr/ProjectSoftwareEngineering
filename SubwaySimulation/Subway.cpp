//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>

#include "Station.h"
#include "Tram.h"
#include "Subway.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

using namespace std;

Subway::Subway() {
  _initCheck = this;

  // Import empty station and tram arrays
  importData({}, {});
  resetCurrentTime();
  ENSURE(getStationsCount() == 0, "Stations count must be initially zero");
  ENSURE(getCurrentTime() == 0, "Current time must be initially zero");
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Subway::properlyInitialized() {
  return _initCheck == this;
}

void Subway::importData(vector<Station *> stations, vector<Tram *> trams) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling importData");
  _stationsArray = stations;
  _tramsArray = trams;
  ENSURE(this->getStationsCount() >= 0, "Stations count must be zero or positive");
  ENSURE(this->getTramsCount() >= 0, "Trams count must be zero or positive");
}

int Subway::getStationsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  unsigned long size = _stationsArray.size();
  return size;
}

int Subway::getTramsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  unsigned long size = _tramsArray.size();
  return size;
}

vector<Station*> Subway::getStations() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStations");
  return _stationsArray;
}

void Subway::reset() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling reset");
  _stationsArray.clear();
  _tramsArray.clear();
  ENSURE(this->getStationsCount() == 0, "Stations map must be cleared");
}

void Subway::computeAutomaticSimulation(int steps, ostream &outputStream, ostream& statsStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  REQUIRE(ValidIntegerAttribute(steps), "Number of steps must be positive");

  resetCurrentTime();

  statsStream << "Time,Vehicle,Line,Action,Station,Turnover,Capacity" << endl;

  while (getCurrentTime() < steps) {
    this->moveTramsOnce(outputStream, statsStream);
    incrementTime();
  }

  ENSURE(getCurrentTime() == steps, "Time must be equal to number of steps");
}

void Subway::moveTramsOnce(ostream &outputStream, ostream& statsFile) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling moveTramsOnce");
  for (auto tram : this->_tramsArray) {
    tram->move(getCurrentTime(), outputStream, statsFile);
  }
}

void Subway::resetCurrentTime() {
  _time = 0;
}

int Subway::getCurrentTime() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTime");
  return _time;
}

void Subway::incrementTime() {
  int previous = getCurrentTime();
  _time++;
}

vector<Tram*> Subway::getTrams() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTracks");
  return _tramsArray;
}

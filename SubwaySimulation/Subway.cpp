//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <unordered_map>

#include "tinyxml.h"
#include "Station.h"
#include "Tram.h"

#include "Subway.h"
#include "DesignByContract.h"

using namespace std;

Subway::Subway() {
  _initCheck = this;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Subway::properlyInitialized() {
  return _initCheck == this;
}

int Subway::getTramsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  return _trams.size();
}

int Subway::getStationsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  return _stations.size();
}

string Subway::toString() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");

  string outputString = "";
    for (auto & station : this->_stationsArray) {
      outputString = outputString + "Station " + station->getName() + "\n" +
             "<- Station " + station->getPrevious() + "\n" +
             "-> Station " + station->getNext() + "\n" +
             "Track " + to_string(station->getTrack()) + "\n";

        // If there's a tram associated to the track, print capacity
        if (this->_trams.count(station->getTrack())) {
            Tram *tram = this->_trams[station->getTrack()];
            if (tram->getStartStation() == station->getName()) {
              outputString = outputString + ": Tram with " + to_string(tram->getCapacity()) + " seats";
            }
        }
    }
    return outputString;
}

void Subway::computeSimulation(int steps) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeSimulation");
}

//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <unordered_map>

#include "Station.h"
#include "Tram.h"
#include "Subway.h"
#include "DesignByContract.h"

using namespace std;

Subway::Subway() {
  _initCheck = this;

  // Import empty station and tram arrays
  importData({}, {});

  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Subway::properlyInitialized() {
  return _initCheck == this;
}

void Subway::importData(vector<Station*> stations, vector<Tram*> trams) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling importData");
  _stationsArray = stations;
  _tramsArray = trams;

  // Fill stations map
  for (auto station : _stationsArray) {
    _stationsMap[station->getName()] = station;
  }

  // Fill trams map
  for (auto tram : _tramsArray) {
    _tramsMap[tram->getLine()] = tram;
  }
  ENSURE(this->getTramsCount() >= 0, "Trams number are negative");
  ENSURE(this->getStationsCount() >= 0, "Stations number are negative");
}


int Subway::getTramsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  int size = _tramsMap.size();
  ENSURE(size >= 0, "Number of trams inside the subway can't negative");
  return size;
}

int Subway::getStationsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  int size = _stationsMap.size();
  ENSURE(size >= 0, "Stations inside the subway can't be negative");
  return size;
}

string Subway::toString() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");

  string outputString = "";
    for (auto & station : this->_stationsArray) {
      outputString = outputString + "Station " + station->getName() + "\n" +
             "<- Station " + station->getPrevious() + "\n" +
             "-> Station " + station->getNext() + "\n" +
             "Track " + to_string(station->getTrack());

        // If there's a tram associated to the track, print capacity
        if (this->_tramsMap.count(station->getTrack())) {
            Tram *tram = this->_tramsMap[station->getTrack()];
            if (tram->getStartStation() == station->getName()) {
              outputString = outputString + ": Tram with " + to_string(tram->getCapacity()) + " seats";
            }
        }
      outputString += "\n";
    }
    return outputString;
}

void Subway::clear() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling clear");
  _stationsArray.clear();
  _tramsArray.clear();
  _stationsMap.clear();
  _tramsMap.clear();
  ENSURE(_stationsArray.size() == 0, "Stations array must be cleared");
  ENSURE(_tramsArray.size() == 0, "Trams array must be cleared");
  ENSURE(_stationsMap.size() == 0, "Stations map must be cleared");
  ENSURE(_tramsMap.size() == 0, "Trams map must be cleared");
}

void Subway::computeAutomaticSimulation(int steps, ostream& outputStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  REQUIRE(steps >= 0, "Number of steps must be positive");

  int current = 0;
  while (current < steps) {
	  this->moveTramsOnce(outputStream);
	  current++;
  }
  ENSURE(current <= steps, "Subway doesn't halted the simulation when reach n steps");
}

void Subway::moveTramsOnce(ostream& outputStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  for (auto tram : this->_tramsArray) {
    string currentStationName = tram->getCurrentStation();
    Station *currentStation = _stationsMap[currentStationName];
    string nextStationName = currentStation->getNext();
    string previousStationName = currentStation->getPrevious();
    string nextState;
    if (nextStationName == tram->getStartStation() && tram->getDirection() == Forward) {
      // Edge case: reaching the end of the line
      tram->switchDirection();
      nextState = previousStationName; 
    } else if (currentStationName == tram->getStartStation() && tram->getDirection() == Backward) {
      // Edge case: reaching the start of the line
      tram->switchDirection();
      nextState = nextStationName;
    } else if (tram->getDirection() == Forward) {
      nextState = nextStationName;
    } else if (tram->getDirection() == Backward) {
      nextState = previousStationName;
    }

    tram->setCurrentStation(nextState);
    outputStream << "Tram " << tram->getLine() << " moved from station " << currentStationName <<
                 " to station " << nextState << endl;
    ENSURE(tram->getCurrentStation() == nextState, "Tram didn't move from its starting position");
  }
}

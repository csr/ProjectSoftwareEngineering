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
}


int Subway::getTramsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  return _tramsMap.size();
}

int Subway::getStationsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  return _stationsMap.size();
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

void Subway::movingTrams(std::ostream& outputStream) {
    for (auto tram : this->_tramsArray) {
	    string position = tram->getCurrentStation();
	    unordered_map<string, Station*>::iterator currentStation = this->_stationsMap.find(position);

	    if (currentStation == this->_stationsMap.end()) {
          outputStream << "Tram not found";
        } else {
          tram->setCurrentStation(currentStation->second->getName());
	    }
	      // What if there's only one station in the system?
	      // E.g. station "A" has "A" as its next and "A" as it's previous.
//            ENSURE(position != tram->getCurrentStation(), "Tram is not moved");
        outputStream << "Tram " << tram->getLine() << "moved from Station" << position <<
		    "to Station" << tram->getCurrentStation() << endl;
    }
 }


void Subway::clear() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling clear");
  _stationsArray.clear();
  _tramsArray.clear();
  _stationsMap.clear();
  _tramsMap.clear();
}

void Subway::computeSimulation(int steps, std::ostream& outputStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeSimulation");

  for (int current = 0; current < steps; ++current){
	  this->movingTrams(outputStream);
  }
}

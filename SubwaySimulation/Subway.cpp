//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <fstream>

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
  setInitialTime();
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  ENSURE(getTramsCount() == 0, "default constructor should return build empty subway");
  ENSURE(getStationsCount() == 0, "default constructor should return build empty subway");
}

bool Subway::properlyInitialized() {
  return _initCheck == this;
}

vector<Tram*> Subway::getTrams() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTracks");
  return _tramsArray;
}

int Subway::getCurrentTime() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTime");
  ENSURE(_time >= 0, "Time can't be negative");
  return _time;
}

void Subway::importData(vector<Station *> stations, vector<Tram *> trams) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling importData");
  _stationsArray = stations;
  _tramsArray = trams;

  // Fill stations map
  for (auto station : _stationsArray) {
    _stationsMap[station->getName()] = station;
  }

  // Fill trams map
  for (auto tram : _tramsArray) {
    _tramsMap[make_pair(tram->getLine(), tram->getNumber())] = tram;
    int track = tram->getLine();
    tram->getCurrentStation()->getTrack(track)->setOccupied(true);
  }
  ENSURE(this->getTramsCount() >= 0, "Trams number are negative");
  ENSURE(this->getStationsCount() >= 0, "Stations number are negative");
}

int Subway::getTramsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  unsigned long size = _tramsMap.size();
  ENSURE(ValidIntegerAttribute(size), "Trams count can't be negative");
  return size;
}

int Subway::getStationsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  unsigned long size = _stationsMap.size();
  ENSURE(ValidIntegerAttribute(size), "Stations count can't be negative");
  return size;
}

string Subway::toString() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");

  string outputString;

  for (auto &station : this->_stationsArray) {
    outputString += + "Station " + station->getName();

    unordered_map<int, Track*> tracks = station->getTracks();

    // Iterate over tracks and print track details
    for (auto *track : station->getTracksArray()) {
      outputString += "\nTrack " + to_string(track->getTrack()) + "\n" +
          "<- Station " + track->getPrevious()->getName() + "\n" +
          "-> Station " + track->getNext()->getName();

      // Check if there's a tram with same line and station
      for (auto &tram: this->_tramsArray) {
        if (tram->getLine() == track->getTrack() && tram->getCurrentStation()->getName() == station->getName()) {
          outputString += "\nTram with " + to_string(tram->getMaxCapacity()) + " seats";
        }
      }
    }
    outputString += "\n\n";
  }
  return outputString;
}

vector<Station*> Subway::getStations() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStations");
  return _stationsArray;
}

void Subway::reset() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling reset");
  _stationsArray.clear();
  _tramsArray.clear();
  _stationsMap.clear();
  _tramsMap.clear();
  ENSURE(this->getTramsCount() == 0, "Trams array must be cleared");
  ENSURE(this->getStationsCount() == 0, "Stations map must be cleared");
}

void Subway::computeAutomaticSimulation(int steps, ostream &outputStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  REQUIRE(steps >= 0, "Number of steps must be positive");

  ofstream nullFile;
  nullFile.setstate(ios_base::badbit);

  while (getCurrentTime() < steps) {
    this->moveTramsOnce(outputStream, nullFile);
    incrementTime();
  }
}

void Subway::computeAutomaticSimulationStats(int steps, ostream &statsStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  REQUIRE(steps >= 0, "Number of steps must be positive");

  ofstream nullFile;
  nullFile.setstate(ios_base::badbit);

  while (getCurrentTime() < steps) {
    this->moveTramsOnce(nullFile, statsStream);
    incrementTime();
  }
}

void Subway::printStatsData(bool isLeaving, Tram *tram, ostream &statsStream) {
  int time = getCurrentTime();
  statsStream << time << "," << tram->getLine();
}

void Subway::moveTramsOnce(ostream &outputStream, ostream &statsStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling moveTramsOnce");
  for (auto tram : this->_tramsArray) {
    Station *currentStation = tram->getCurrentStation();
    string previousStationName = currentStation->getName();
    if (tram->getDistance() == 0) {
      if(tram->getWaiting() == 0) {
        Track *track = currentStation->getTrack(tram->getNumber());
        if (tram->trackFree()) {
          //Leave a station
          tram->leave();
          printStatsData(true, tram, statsStream);
        }
      }else {
        tram->decreaseWaiting();
      }
    } else if(tram->getDistance() == 1) {
      //Arrive in a Station
      tram->decreaseDistance();
      tram->arrive();
      string currentStationName = tram->getCurrentStation()->getName();
      outputStream << "Tram " << tram->getLine() << " moved from station " << previousStationName <<
                   " to station " << currentStationName << " at time " << getCurrentTime() << endl;
      printStatsData(false, tram, statsStream);
    }else
      tram->decreaseDistance();
  }
}

void Subway::setInitialTime() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling setInitialTime");
  _time = 0;
  ENSURE(_time == 0, "Time wasn't set to 0");
}

void Subway::incrementTime() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling incrementTime");
  int previous = getCurrentTime();
  _time++;
  ENSURE(getCurrentTime() == previous + 1, "Time wasn't incremented in incrementTime");
}



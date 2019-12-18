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
  resetCurrentTime();
  ENSURE(getTramsCount() == 0, "Trams count must be initially zero");
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

  // Fill stations map
  for (auto station : _stationsArray) {
    _stationsMap[station->getName()] = station;
  }

  // Fill trams map
  for (auto tram : _tramsArray) {
    _tramsMap[make_pair(tram->getLine(), tram->getVehicle())] = tram;
    int track = tram->getLine();
    tram->getCurrentStation()->getTrack(track)->setOccupied(true);
  }
  ENSURE(this->getTramsCount() >= 0, "Trams count must be zero or positive");
  ENSURE(this->getStationsCount() >= 0, "Stations count must be zero or positive");
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

void Subway::printStatsData(bool isLeaving, Tram *tram, ostream &statsStream) {
  int time = getCurrentTime();
  string arrivingLeavingStr = isLeaving ? "Leaving" : "Arriving";
  Station *currentStation = tram->getCurrentStation();
  string stationName = currentStation->getName();
  int turnover = tram->getTurnover();
  int currentCapacity = tram->getCurrentCapacity();

  statsStream << ConvertSecondsToTimeString(time) << ","
              << tram->getVehicle() << ","
              << tram->getLine() << ","
              << arrivingLeavingStr << ","
              << stationName << ","
              << ToString(turnover) << ","
              << ToString(currentCapacity)
              << endl;
}

void Subway::moveTramsOnce(ostream &outputStream, ostream& statsFile) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling moveTramsOnce");
  outputStream.flush();
  for (auto tram : this->_tramsArray) {
    Station *currentStation = tram->getCurrentStation();
    string previousStationName = currentStation->getName();
    if (tram->getDistance() == 0) {
      if(tram->getWaiting() == 0) {
        Track *track = currentStation->getTrack(tram->getVehicle());
        if (tram->trackFree()) {
          //Leave a station
          tram->leave();
          printStatsData(true, tram, statsFile);
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
                   " to station " << currentStationName << " at time " << ConvertSecondsToTimeString(getCurrentTime()) << endl;
      printStatsData(false, tram, statsFile);
    }else {
      tram->decreaseDistance();
    }
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

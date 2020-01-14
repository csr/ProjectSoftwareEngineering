//============================================================================
// Name        : Track.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>

#include "Tram.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

Tram::Tram(int line, TramType type, string startStation, int number) {
  _initCheck = this;
  _line = line;
  _type = type;
  _number = number;
  _turnover = 0;
  _waitingTime = 0;
  _distance = 0;
  setCurrentStationName(startStation);

  setCurrentCapacity(0);

  ENSURE(line == getLine(), "Line wasn't set correctly in constructor");
  ENSURE(type == getType(), "Type wasn't set correctly in constructor");
  ENSURE(number == getVehicle(), "Number wasn't set correctly in constructor");
  ENSURE(startStation == getCurrentStationName(), "Start station wasn't set correctly in constructor");
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Tram::properlyInitialized() {
  return _initCheck == this;
}

void Tram::move(int time, ostream &outputStream, ostream &statsFile) {
  Station *currentStation = getCurrentStation();
  string previousStationName = currentStation->getName();
  if (_distance == 0) {
    if(_waitingTime == 0) {
      Track *track = currentStation->getTrack(getVehicle());
      if (trackFree()) {
        //Leave a station
        leaveStation();
        printCSVData(time, true, statsFile);
      }
    } else {
      _waitingTime -= 1;
    }
  } else if (_distance == 1) {
    _distance--;
    arriveToStation();
    string currentStationName = getCurrentStation()->getName();
    outputStream << "Tram " << getLine() << " moved from station " << previousStationName <<
                 " to station " << currentStationName << " at time " << ConvertSecondsToTimeString(time) << endl;
    printCSVData(time, false, statsFile);
  } else {
    _distance--;
  }
}

int Tram::getLine() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  return _line;
}


int Tram::getSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  return _speed;
}

Station* Tram::getCurrentStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  return _currentStation;
}

string Tram::getCurrentStationName() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStationName");
  return _currentStationName;
}

TramType Tram::getType() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getType");
  return _type;
}

int Tram::getVehicle() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getVehicle");
  return _number;
}

int Tram::getCurrentCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentCapacity");
  return _currentCapacity;
}

void Tram::setCurrentStation(Station *station) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  _currentStation = station;
  _currentStation->getTrack(this->getLine())->setOccupied(true);
  setCurrentStationName(station->getName());
  ENSURE(station->getTrack(this->getLine())->isCurrentlyOccupied(), "Station must be set to occupied");
  ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
}

void Tram::setCurrentStationName(string currentStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  _currentStationName = currentStation;
  ENSURE(getCurrentStationName() == currentStation, "Tram start station name was not set correctly");
}

void Tram::arriveToStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling arriveToStation");
  Station* currentStation = this->getCurrentStation();
  Track *track = currentStation->getTrack(this->getLine());
  Station* nextStation = getNextStation();
  this->setCurrentStation(nextStation);
  this->getCurrentStation()->getTrack(this->getLine())->setOccupied(true);

  int randomNumber = GenerateRandomNumber(0, this->getCurrentCapacity());
  setCurrentCapacity(getCurrentCapacity()-randomNumber);

  ENSURE(this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't arriveToStation in the next station");
}

void Tram::leaveStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling leaveStation");

  int newPassengersCount = GenerateRandomNumber(0, getMaxCapacity() - getCurrentCapacity());
  setCurrentCapacity(getCurrentCapacity() + newPassengersCount);

  // Update turnover
  _turnover += 2 * newPassengersCount;
  _distance = calculateDistance();

  _waitingTime = 60;
  this->getCurrentStation()->getTrack(this->getLine())->setOccupied(false);
  ENSURE(!this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't leaveStation the station");
}

void Tram::setCurrentCapacity(int number) {
//  cout << "Setting capacity to: " << ToString(number) << endl;
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
  _currentCapacity = number;
  ENSURE(getCurrentCapacity() <= getMaxCapacity(), "Tram currentCapacity can't be greater than maximum capacity");
  ENSURE(getCurrentCapacity() >= 0, "Tram currentCapacity must be positive");
  ENSURE(number == getCurrentCapacity(), "Tram currentCapacity was not set correctly");
}


void Tram::printCSVData(int time, bool isLeaving, ostream &statsStream) {
  string arrivingLeavingStr = isLeaving ? "Leaving" : "Arriving";
  Station *currentStation = getCurrentStation();
  string stationName = currentStation->getName();
  int currentCapacity = getCurrentCapacity();

  statsStream << ConvertSecondsToTimeString(time) << ","
              << getVehicle() << ","
              << getLine() << ","
              << arrivingLeavingStr << ","
              << stationName << ","
              << ToString(_turnover) << ","
              << ToString(currentCapacity)
              << endl;
}
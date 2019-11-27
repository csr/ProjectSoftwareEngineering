//============================================================================
// Name        : Track.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include "Tram.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

Tram::Tram(int line, TramType type, string startStation, int number) {
  _initCheck = this;
  setLine(line);
  setStartStationName(startStation);
  setType(type);
  setNumber(number);
  ENSURE(line == getLine(), "Line wasn't set correctly in constructor");
  ENSURE(startStation == getStartStationName(), "Start station wasn't set correctly in constructor");
}

bool Tram::properlyInitialized() {
  return _initCheck == this;
}

int Tram::getLine() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  return _line;
}

int Tram::getMaxCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
  return _maxCapacity;
}

int Tram::getSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  return _speed;
}

Station* Tram::getStartStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  return _startStation;
}

Station* Tram::getCurrentStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  return _currentStation;
}

string Tram::getStartStationName() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStationName");
  return _startStationName;
}

TramType Tram::getType() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getType");
  return _type;
}

int Tram::getNumber() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getNumber");
  return _number;
}

void Tram::setLine(int line) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  _line = line;
  ENSURE(ValidIntegerAttribute(getLine()), "Tram line can't be negative");
  ENSURE(line == getLine(), "Tram line was not set correctly");
}

void Tram::setStartStation(Station *startStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
  _startStation = startStation;
  ENSURE(startStation == getStartStation(), "Tram start station was not set correctly");
}

void Tram::setCurrentStation(Station *station) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  _currentStation = station;
  ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
}

void Tram::setStartStationName(string startStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  _startStationName = startStation;
  ENSURE(startStation == getStartStationName(), "Tram start station name was not set correctly");
}

void Tram::setType(TramType type) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setType");
  _type = type;
  ENSURE(type == getType(), "Tram type was not set correctly");
}

void Tram::setNumber(int number) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setTrack");
  _number = number;
  ENSURE(number == getNumber(), "Tram vehicleNumber was not set correctly");
}

void Tram::move() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
  Station *currentStation = this->getCurrentStation();
  int passengers = GenerateRandomNumber(this->getCurrentCapacity(), this->getMaxCapacity());
  setCurrentCapacity(passengers); // controllare
  setTurnover();

  // Set next station
  Track track = currentStation->getTrack(this->getNumber());
  Station *nextStation = track.getNextStation();
  this->setCurrentStation(nextStation);

  passengers = GenerateRandomNumber(0, this->getCurrentCapacity());
  setCurrentCapacity(passengers);
}

void Tram::setCurrentCapacity(int number) {
    REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
    _currentCapacity = number;
    ENSURE(getCurrentCapacity() <= getMaxCapacity(), "Tram currentCapacity is greater than maximum capacity");
    ENSURE(number == getCurrentCapacity(), "Tram currentCapacity was not set correctly");
}

int Tram::getTurnover() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getTurnover");
  return _turnover;
}

void Tram::setTurnover() {
    REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setTurnover");
    _turnover = 2 * getCurrentCapacity();
}

void Tram::setSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  if(this->_type == Albatross) {
    _speed = 70;
  } else if (this->_type == PCC) {
    _speed = 40;
  }
}

int Tram::getCurrentCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentCapacity");
  return _currentCapacity;
}


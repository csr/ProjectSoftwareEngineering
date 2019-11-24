//============================================================================
// Name        : Tram.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This class is the blueprint for the Tram object.
//============================================================================

#include "Tram.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

Tram::Tram(int line, TramType type, string startStation) {
  _initCheck = this;
  setLine(line);
  setStartStationName(startStation);
  setType(type);
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

int Tram::getCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
  switch (_type) {
    case Albatross: {
      return 72;
    }
    case PCC: {
      return 16;
    }
  }
}

int Tram::getSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  switch (_type) {
    case Albatross: {
      return 70;
    }
    case PCC: {
      return 40;
    }
  }
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
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setNumber");
  _number = number;
  ENSURE(number == getNumber(), "Tram type was not set correctly");
}

void Tram::move() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
  Station *currentStation = this->getCurrentStation();
  Station *nextStation = currentStation->getNext();
  this->setCurrentStation(nextStation);
}
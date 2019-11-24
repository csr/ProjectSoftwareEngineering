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

Tram::Tram(int line, int capacity, int speed, string startStation) {
  _initCheck = this;
  setLine(line);
  setCapacity(capacity);
  setSpeed(speed);
  setStartStationName(startStation);

  ENSURE(line == getLine(), "Line wasn't set correctly in constructor");
  ENSURE(capacity == getCapacity(), "Capacity wasn't set correctly in constructor");
  ENSURE(speed == getSpeed(), "Speed wasn't set correctly in constructor");
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
  return _capacity;
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

string Tram::getCurrentStationName() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStationName");
  return _currentStationName;
}

void Tram::setLine(int line) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  _line = line;
  ENSURE(ValidIntegerAttribute(getLine()), "Tram line can't be negative");
  ENSURE(line == getLine(), "Tram line was not set correctly");
}

void Tram::setCapacity(int capacity) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCapacity");
  _capacity = capacity;
  ENSURE(ValidIntegerAttribute(getCapacity()), "Tram capacity can't be negative");
  ENSURE(capacity == getCapacity(), "Tram capacity was not set correctly");
}

void Tram::setSpeed(int speed) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  _speed = speed;
  ENSURE(ValidIntegerAttribute(getSpeed()), "Tram speed can't be negative");
  ENSURE(speed == getSpeed(), "Tram speed was not set correctly");
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

void Tram::setCurrentStationName(string currentStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStationName");
  _currentStationName = currentStation;
  ENSURE(currentStation == getCurrentStationName(), "Tram current station name was not set correctly");
}

void Tram::move() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
  Station *currentStation = this->getCurrentStation();
  Station *nextStation = currentStation->getNext();
  this->setCurrentStation(nextStation);
}
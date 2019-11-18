//============================================================================
// Name        : Tram.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This class is the blueprint for the Tram object.
//============================================================================

#include "Tram.h"
#include "DesignByContract.h"

Tram::Tram(int line, int capacity, int speed, string startStation) {
  _initCheck = this;
  _line = line;
  _capacity = capacity;
  _speed = speed;
  _startStation = startStation;
  _currentStation = _startStation;
  _direction = Forward;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool validDirection(TramDirection direction) {
  return direction == Backward || direction == Forward;
}

int Tram::getLine() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  ENSURE(validIntegerAttribute(_line), "Tram number must be positive");
  return _line;
}

int Tram::getCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
  ENSURE(validIntegerAttribute(_capacity), "Tram capacity must be positive");
  return _capacity;
}

int Tram::getSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  ENSURE(validIntegerAttribute(_speed), "Tram speed must be positive");
  return _speed;
}

string Tram::getStartStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  ENSURE(validStringAttribute(_startStation), "Start station must be valid");
  return _startStation;
}

string Tram::getCurrentStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  ENSURE(validStringAttribute(_currentStation), "Current station must be valid");
  return _currentStation;
}

TramDirection Tram::getDirection() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getDirection");
  ENSURE(validDirection(_direction), "Tram direction must be either backward or forward");
  return _direction;
}

void Tram::setLine(int line) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  _line = line;
  ENSURE(validIntegerAttribute(_line), "The number of a line is negative");
}

void Tram::setCapacity(int capacity) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCapacity");
  _capacity = capacity;
  ENSURE(validIntegerAttribute(_capacity), "Tram capacity is negative");
}

void Tram::setSpeed(int speed) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  _speed = speed;
  ENSURE(validIntegerAttribute(_speed), "Tram speed is negative");
}

void Tram::setStartStation(string startStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
  _startStation = startStation;
  ENSURE(validStringAttribute(_startStation), "Tram start station is empty");
}

void Tram::setCurrentStation(string station) {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
	_currentStation = station;
	ENSURE(validStringAttribute(_currentStation), "Tram current station is empty");
}

void Tram::switchDirection() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling switchDirection");
  _direction = _direction == Forward ? Backward : Forward;
  ENSURE(validDirection(_direction), "Tram direction must be valid");
}
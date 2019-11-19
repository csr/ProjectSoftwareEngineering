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

string Tram::getStartStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  return _startStation;
}

string Tram::getCurrentStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  return _currentStation;
}

TramDirection Tram::getDirection() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getDirection");
  return _direction;
}

void Tram::setLine(int line) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  _line = line;
  ENSURE(validIntegerAttribute(getLine()), "The number of a line is negative");
}

void Tram::setCapacity(int capacity) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCapacity");
  _capacity = capacity;
  ENSURE(validIntegerAttribute(getCapacity()), "Tram capacity is negative");
}

void Tram::setSpeed(int speed) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  _speed = speed;
  ENSURE(validIntegerAttribute(getSpeed()), "Tram speed is negative");
}

void Tram::setStartStation(string startStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
  _startStation = startStation;
  ENSURE(validStringAttribute(getStartStation()), "Tram start station is empty");
}

void Tram::setCurrentStation(string station) {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
	_currentStation = station;
	ENSURE(validStringAttribute(getCurrentStation()), "Tram current station is empty");
}

void Tram::switchDirection() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling switchDirection");
  TramDirection previousDirection = this->getDirection();
  _direction = _direction == Forward ? Backward : Forward;
  ENSURE(previousDirection != this->getDirection(), "Tram direction must be valid");
}
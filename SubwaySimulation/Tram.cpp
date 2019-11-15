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

bool Tram::properlyInitialized() {
  return _initCheck == this;
}

int Tram::getLine() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  ENSURE(validLine(), "Tram number is negative");
  return _line;
}

int Tram::getCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
  ENSURE(validCapacity(), "Tram capacity is negative");
  return _capacity;
}

int Tram::getSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  ENSURE(validSpeed(), "Tram speed is negative");
  return _speed;
}

string Tram::getStartStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  ENSURE(validStation(_startStation), "Start station is null");
  return _startStation;
}

string Tram::getCurrentStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  ENSURE(validStation(_currentStation), "Current station is null");
  return _currentStation;
}

TramDirection Tram::getDirection() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  ENSURE(validDirection(), "Tram direction is not backward or forward");
  return _direction;
}

void Tram::setLine(int line) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  _line = line;
  ENSURE(validLine(), "The number of a line is negative");
}

void Tram::setCapacity(int capacity) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCapacity");
  _capacity = capacity;
  ENSURE(validCapacity(), "Tram capacity is negative");
}

void Tram::setSpeed(int speed) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  _speed = speed;
  ENSURE(validSpeed(), "Tram speed is negative");
}

void Tram::setStartStation(string startStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
  _startStation = startStation;
  ENSURE(validStation(_startStation), "Tram start station is empty");
}

void Tram::setCurrentStation(string station) {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
	_currentStation = station;
	ENSURE(validStation(_currentStation), "Tram current station is empty");
}

void Tram::switchDirection() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling switchDirection");
  _direction = _direction == Forward ? Backward : Forward;
  ENSURE(validDirection(), "Tram direction is wrong");
}

bool Tram::validDirection(){
	return _direction == Backward || _direction == Forward;
}

bool Tram::validCapacity(){
	return _capacity >= 0;
}

bool Tram::validLine(){
	return _line >= 0;
}

bool Tram::validSpeed(){
	return _speed >= 0;
}

bool Tram::validStation(string station){
	return station != "";
}

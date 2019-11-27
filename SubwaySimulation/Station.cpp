//============================================================================
// Name        : Station.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This class is the blueprint for the Station object.
//============================================================================

#include <iostream>
#include "Station.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

using namespace std;

Station::Station(string name, string nextStation, string previousStation, StationType type) {
  _initCheck = this;
  setName(name);
  setType(type);
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Station::properlyInitialized() {
  return _initCheck == this;
}

string Station::getName() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getName");
  return _name;
}

Station* Station::getNext() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNext");
  return _next;
}

Station* Station::getPrevious() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPrevious");
  return _previous;
}

string Station::getNextName() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNextName");
  return _nextName;
}

string Station::getPreviousName() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPreviousName");
  return _previousName;
}

int Station::getTrack() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");
  return _track;
}

StationType Station::getType() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getType");
  return _type;
}

bool Station::isCurrentlyOccupied() {
    REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling isCurrentlyOccupied");
    return _isCurrentlyOccupied;
}

void Station::setName(string name) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setName");
  _name = name;
  ENSURE(ValidStringAttribute(getName()), "Station name must be valid");
  ENSURE(getName() == name, "Station name was not set correctly");
}

void Station::setNext(Station* next) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNext");
  _next = next;
  ENSURE(getNext() == next, "Station next station was not set correctly");
}

void Station::setPrevious(Station* previous) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPrevious");
  _previous = previous;
  ENSURE(getPrevious() == previous, "Station previous station was not set correctly");
}

void Station::setNextName(string next) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNextName");
  _nextName = next;
  ENSURE(ValidStringAttribute(getNextName()), "Station next name must be valid");
  ENSURE(getNextName() == _nextName, "Station next station name was not set correctly");
}

void setType(StationType type) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setType");
  _type = type;
  ENSURE(type == getType(), "Station previous station name was not set correctly");
}

void Station::setOccupied(bool isOccupied) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setOccupied");
  _isCurrentlyOccupied = isOccupied;
  ENSURE(isOccupied == isCurrentlyOccupied(), "Station occupied was not set correctly");
}
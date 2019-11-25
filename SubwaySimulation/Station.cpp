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

Station::Station(string name, string next, string previous, int track, StationType type) {
  _initCheck = this;
  setName(name);
  setNextName(next);
  setPreviousName(previous);
  setTrack(track);
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

bool Station::isOccupy() {
    REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling isOccupy");
    return _occupy;
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

void Station::setPreviousName(string previous) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPreviousName");
  _previousName = previous;
  ENSURE(ValidStringAttribute(getPreviousName()), "Station next name must be valid");
  ENSURE(getPreviousName() == _previousName, "Station previous station name was not set correctly");
}

void Station::setTrack(int track) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTrack");
  _track = track;
  ENSURE(ValidIntegerAttribute(getTrack()), "Station track number can't be negative");
  ENSURE(getTrack() == track, "Station track number was not set correctly");
}

void Station::setType(StationType type) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setType");
  _type = type;
  ENSURE(type == getType(), "Station previous station name was not set correctly");
}

void Station::setOccupy(bool response){
    REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setOccupy");
    _occupy = response;
    ENSURE(response == isOccupy(), "Station occupy was not set correctly");
}
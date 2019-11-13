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

using namespace std;

Station::Station(string name, string next, string previous, int track) {
  _initCheck = this;
  _name = name;
  _next = next;
  _previous = previous;
  _track = track;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Station::properlyInitialized() {
  return _initCheck == this;
}

string Station::getName() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getName");
  return _name;
}

string Station::getNext() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNext");
  return _next;
}

string Station::getPrevious() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPrevious");
  return _previous;
}

int Station::getTrack() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");
  return _track;
}

void Station::setName(string name) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setName");
  _name = name;
}

void Station::setNext(string next) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNext");
  _next = next;
}

void Station::setPrevious(string previous) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPrevious");
  _previous = previous;
}

void Station::setTrack(int track) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTrack");
  _track = track;
}
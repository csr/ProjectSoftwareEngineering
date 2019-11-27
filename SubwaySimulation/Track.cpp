//============================================================================
// Name        : Track.cpp
// Author      : Group A
// Version     :
// Copyright   : Group A
// Description : Subway simulation in C++
//============================================================================

#include "Track.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

Track::Track(int track, Station* next, Station* previous) {
  _init = this;
  setTrack(track);
  setNext(next);
  setPrevious(previous);
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Track::properlyInitialized() {
  return _init == this;
}

void Track::setTrack(int number) {
  REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
  _track = number;
  ENSURE(ValidIntegerAttribute(number), "Number of track is negative");
  ENSURE(number == getNumber(), "Number of track is negative");
}

void Track::setNext(Station *next) {
  REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
  _next = next;
  ENSURE(next == getNext(), "Next station wasn't set correctly");
}

void Track::setPrevious(Station *previous) {
  REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling setPrevious");
  _previous = previous;
  ENSURE(previous == getPrevious(), "Previous station wasn't set correctly");
}

int Track::getNumber() {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getNumber");
    return _track;
}

Station* Track::getNext() {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getNext");
    return _next;
}

Station* Track::getPrevious() {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getPrevious");
    return _previous;
}
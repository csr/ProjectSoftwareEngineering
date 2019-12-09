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

Station::Station(string name, StationType type, unordered_map<int, Track*> tracks) {
  _initCheck = this;
  setName(name);
  _type = type;
  setTracks(tracks);
  setOccupied(false);
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Station::properlyInitialized() {
  return _initCheck == this;
}

void Station::setName(string name) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setName");
  _name = name;
  ENSURE(ValidStringAttribute(getName()), "Station name must be valid");
  ENSURE(getName() == name, "Station name was not set correctly");
}

void Station::setOccupied(bool isOccupied) {
// Mi dà errore - @cdecal
//  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setOccupied");
  _isOccupied = isOccupied;
  ENSURE(isOccupied == isCurrentlyOccupied(), "Station occupied was not set correctly");
}

void Station::setTracks(unordered_map<int, Track*> tracks) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTracks");
  _tracks = tracks;
  ENSURE(tracks == getTracks(), "Station tracks weren't set correctly");
}

string Station::getName() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getName");
  return _name;
}

Track* Station::getTrack(int number) {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");
  if (_tracks.count(number)) {
    return _tracks[number];
  } else {
    return NULL;
  }
}

unordered_map<int, Track*> Station::getTracks() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTracks");
  return _tracks;
}

vector<Track*> Station::getTracksArray() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTracksArray");

  // Get tracks array
  vector<Track*> tracksVector;
  tracksVector.reserve(_tracks.size());

  for(auto keyValuePair : _tracks) {
    tracksVector.push_back(keyValuePair.second);
  }

  return tracksVector;
}

StationType Station::getType() {
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getType");
  return _type;
}

bool Station::isCurrentlyOccupied() {
  // Mi dà errore - @cdecal
//  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling isCurrentlyOccupied");
  return _isOccupied;
}
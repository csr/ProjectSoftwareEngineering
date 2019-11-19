//============================================================================
// Name        : Station.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#ifndef UNTITLED_STATION_H
#define UNTITLED_STATION_H

#include "SimulationObject.h"

using namespace std;

class Station: public SimulationObject {
 public:

/**
 Constructs a Station class with name, next station, previous station, and track.
 @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 @param name Station name.
 @param next Name of the next Station.
 @param previous Name of the previous Station.
 @param track Station track number.
*/
  Station(string name, string nextStation, string previousStation, int track);

/**
 Returns the Station name.
 @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getName");
 @returns Name of Station.
*/
  string getName();

/**
  Returns the next Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNext");
  @returns Name of next Station.
*/
  string getNext();

/**
  Getter that returns the previous Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPrevious");
  @returns Name of previous Station.
*/
  string getPrevious();

/**
  Getter for Station track number.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");
  @returns Station track number.
*/
  int getTrack();

/**
  Setter for Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setName");
  @note ENSURE(validStringAttribute(getName()), "Station name can't be empty");
  @param name Name of Station name.
*/
  void setName(string name);

/**
  Setter for next Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNext");\n
  @note ENSURE(validStringAttribute(getNext()), "Next station name can't be empty");
  @param next Name of next Station.
*/
  void setNext(string next);

/**
  Setter for previous Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPrevious");\n
  @note ENSURE(validStringAttribute(getPrevious()), "Previous station name can't be empty");
  @param previous Name of previous Station.
*/
  void setPrevious(string previous);

/**
  Setter for Station track.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTrack");\n
  @note ENSURE(validIntegerAttribute(getTrack()), "Station track number can't be negative");
  @param track Station track.
*/
  void setTrack(int track);

 private:
  string _name;
  string _next;
  string _previous;
  int _track;
};

#endif //UNTITLED_STATION_H

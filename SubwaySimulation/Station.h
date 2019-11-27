//============================================================================
// Name        : Station.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#ifndef UNTITLED_STATION_H
#define UNTITLED_STATION_H
#include <cstdlib>
#include <string>

using namespace std;

enum StationType {TypeStation, TypeStop};

class Station {
 public:
/**
 Constructs a Station class with name, next station name, previous station name, and track.
 @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 @param name Station name.
 @param next Next Station name.
 @param previous Previous Station name.
 @param track Station track number.
*/
  Station(string name, string nextStation, string previousStation, StationType type);

  bool properlyInitialized();
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
  Station* getNext();

/**
  Getter that returns the previous Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPrevious");
  @returns Name of previous Station.
*/
  Station* getPrevious();

/**
  Getter for next Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNextName");
*/
  string getNextName();

/**
  Getter for previous Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPreviousName");
*/
  string getPreviousName();

  /**
  Getter for Station track number.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");
  @returns Station track number.
*/
  int getTrack();

  StationType getType();

  bool isCurrentlyOccupied();

/**
  Setter for Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setName");
  @note ENSURE(ValidStringAttribute(getName()), "Station name must be valid");
  @note ENSURE(getName() == name, "Station name was not set correctly");
  @param name Name of Station name.
*/
  void setName(string name);

/**
  Setter for next Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNext");
  @note ENSURE(ValidStringAttribute(getNext()), "Next station name must be valid");
  @note ENSURE(getNext() == next, "Station next station was not set correctly");
  @param next Next Station.
*/
  void setNext(Station* next);

/**
  Setter for previous Station.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPrevious");
  @note ENSURE(ValidStringAttribute(getPrevious()), "Previous station name must be valid");
  @note ENSURE(getPrevious() == previous, "Station previous station was not set correctly");
  @param previous Previous Station.
*/
  void setPrevious(Station* previous);

  void setNextName(string next);

  void setOccupied(bool isOccupied);

 private:
  Station * _initCheck;
  string _name;
  Station* _next;
  Station* _previous;
  string _nextName;
  string _previousName;
  int _track;
  StationType _type;
  bool _isCurrentlyOccupied;
};

#endif //UNTITLED_STATION_H

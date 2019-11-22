//============================================================================
// Name        : Station.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#ifndef UNTITLED_STATION_H
#define UNTITLED_STATION_H

using namespace std;

class Station {
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
  @param next Name of next Station.
*/
  void setNext(string next);

/**
  Setter for previous Station name.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPrevious");
  @note ENSURE(ValidStringAttribute(getPrevious()), "Previous station name must be valid");
  @note ENSURE(getPrevious() == previous, "Station previous station was not set correctly");
  @param previous Name of previous Station.
*/
  void setPrevious(string previous);

/**
  Setter for Station track.
  @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTrack");
  @note ENSURE(ValidIntegerAttribute(getTrack()), "Station track number can't be negative");
  @note ENSURE(getTrack() == track, "Station track number was not set correctly");
  @param track Station track.
*/
  void setTrack(int track);

 private:
  Station * _initCheck;
  string _name;
  string _next;
  string _previous;
  int _track;
};

#endif //UNTITLED_STATION_H

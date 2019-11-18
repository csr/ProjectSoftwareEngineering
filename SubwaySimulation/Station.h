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
 Construct a Station class with name, next station, previous station, and track.

 ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 @param name Station name.
 @param next Name of the next Station.
 @param previous Name of the previous Station.
 @param track Station track number.
*/
  Station(string name, string nextStation, string previousStation, int track);

  bool properlyInitialized();

/**
 Returns the Station name.
 REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getName");\n
 ENSURE(validName(), "Name of station not valid");
*/
  string getName();

/**
  Returns the next Station.
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNext");\n
  ENSURE(validStation(_next), "Next of station not valid");
*/
  string getNext();


/**
  Getter that returns the previous Station.
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPrevious");\n
  ENSURE(validStation(_previous), "Previous of station not valid");
*/
  string getPrevious();

/**
  Getter for track number.
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");\n
  ENSURE(validTrack(), "Track of station not valid");
*/
  int getTrack();

/**
  Setter for Station name.
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setName");\n
  ENSURE(validName(), "Station name can't be empty");
*/
  void setName(string name);

/**
  Setter for next Station.
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNext");\n
  ENSURE(validStation(_next), "Next station name can't be empty");
*/
  void setNext(string next);

/**
  Setter for previous Station.
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPrevious");\n
  ENSURE(validStation(_previous), "Previous station name can't be empty");
*/
  void setPrevious(string previous);

/**
  Setter for Station rack.
  REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTrack");\n
  ENSURE(validTrack(track), "Station track number can't be negative");
*/
  void setTrack(int track);

 private:
  Station * _initCheck; //!use pointer to myself to verify whether I am properly initialized
  string _name;
  string _next;
  string _previous;
  int _track;
};

#endif //UNTITLED_STATION_H

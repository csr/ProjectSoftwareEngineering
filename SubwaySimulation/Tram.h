//============================================================================
// Name        : Tram.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This file holds the header for the Tram class.
//============================================================================

#ifndef UNTITLED_TRAM_H
#define UNTITLED_TRAM_H
#include <string>
#include "Station.h"

using namespace std;

class Tram {
 public:

/**
 Constructs a Tram class with line, capacity, speed, and start Station name.
 @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 @note ENSURE(line == getLine(), "Line wasn't set correctly in constructor");
 @note ENSURE(capacity == getCapacity(), "Capacity wasn't set correctly in constructor");
 @note ENSURE(speed = getSpeed(), "Speed wasn't set correctly in constructor");
 @note ENSURE(startStation = getStartStationName(), "Start station wasn't set correctly in constructor");
 @param line Line of the Tram.
 @param next Capacity of the Tram.
 @param speed Speed of the Tram.
 @param startStation Start Station of the Tram.
 @returns An instance of Tram.
*/
  Tram(int line, int capacity, int speed, string startStation);

  bool properlyInitialized();
/**
  Getter for the line of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  @returns Line of the Tram.
*/
  int getLine();

/**
  Getter for the capacity of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
  @returns Capacity of the Tram.
*/
  int getCapacity();

/**
  Getter for the speed of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  @returns Speed of the Tram.
*/
  int getSpeed();

/**
  Getter for the start Station of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  @returns Start Station of the Tram.
*/
  Station* getStartStation();

/**
  Getter for the current Station name of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  @returns Current Station the tram is at.
*/
  Station* getCurrentStation();

  string getStartStationName();

  string getCurrentStationName();

/**
  Setter for the line of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  @note ENSURE(ValidIntegerAttribute(getLine()), "Tram line can't be negative");
  @note ENSURE(line == getLine(), "Tram line was not set correctly");
  @param line Line of the Tram.
*/
  void setLine(int line);

/**
  Setter for the capacity of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCapacity");
  @note ENSURE(ValidIntegerAttribute(getCapacity()), "Tram capacity can't be negative");
  @note ENSURE(capacity == getCapacity(), "Tram capacity was not set correctly");
  @param capacity Capacity of the Tram.
*/
  void setCapacity(int capacity);

/**
  Setter for the speed of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  @note ENSURE(ValidIntegerAttribute(getSpeed()), "Tram speed can't be negative");
  @note ENSURE(speed == getSpeed(), "Tram speed was not set correctly");
  @param speed Speed of the Tram.
*/
  void setSpeed(int speed);

/**
  Setter for the start Station name.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
  @note ENSURE(ValidStringAttribute(getStartStation()), "Tram start station must be valid");
  @note ENSURE(startStation == getStartStation(), "Tram start station was not set correctly");
  @param startStaton Start Station of the Tram.
*/
  void setStartStation(Station *station);

/**
  Setter for the current start Station name.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  @note ENSURE(ValidStringAttribute(getCurrentStation()), "Tram current station must be valid");
  @note ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
  @param station Start Station.
*/
  void setCurrentStation(Station *station);

  void setStartStationName(string startStation);

  void setCurrentStationName(string currentStation);

  void move();

 private:
  Tram * _initCheck;
  int _line;
  int _capacity;
  int _speed;
  Station* _startStation;
  Station* _currentStation;
  string _startStationName;
  string _currentStationName;
};

#endif //UNTITLED_TRAM_H

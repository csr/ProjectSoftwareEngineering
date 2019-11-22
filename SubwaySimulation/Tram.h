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

using namespace std;

enum TramDirection {Forward, Backward};

class Tram {
 public:

/**
 Constructs a Tram class with line, capacity, speed, and start Station name.
 @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 @param line Line of the Tram.
 @param next Capacity of the Tram.
 @param speed Speed of the Tram.
 @param startStation Start Station name of the Tram.
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
  @returns Start Station name of the Tram.
*/
  string getStartStation();

/**
  Getter for the current Station name of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  @returns Name of the current Station the tram is at.
*/
  string getCurrentStation();

/**
  Getter for the Tram direction.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getDirection");
  @returns The direction the tram is travelling at.
*/
  TramDirection getDirection();

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
  @param startStaton Start Station name of the Tram.
*/
  void setStartStation(string startStation);

/**
  Setter for the current start Station name.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  @note ENSURE(ValidStringAttribute(getCurrentStation()), "Tram current station must be valid");
  @note ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
  @param station Start Station name.
*/
  void setCurrentStation(string station);

/**
  Switches the direction of the Tram. E.g. Forward becomes Backward, and viceversa.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling switchDirection");
  @note ENSURE(previousDirection != this->getDirection(), "Tram direction must be valid");
*/
  void switchDirection();

 private:
  Tram * _initCheck;
  int _line;
  int _capacity;
  int _speed;
  string _startStation;
  string _currentStation;
  TramDirection _direction;
};

#endif //UNTITLED_TRAM_H

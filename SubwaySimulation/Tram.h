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
#import "SimulationObject.h"

using  namespace std;

enum TramDirection {Forward, Backward};

class Tram: public SimulationObject {
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

/**
  Getter for the line of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  @note ENSURE(validIntegerAttribute(_line), "Tram number must be positive");
  @returns Line of the Tram.
*/
  int getLine();


/**
  Getter for the capacity of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
  @note ENSURE(validIntegerAttribute(_capacity), "Tram capacity must be positive");
  @returns Capacity of the Tram.
*/
  int getCapacity();

/**
  Getter for the speed of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  @note ENSURE(validIntegerAttribute(_speed), "Tram speed must be positive");
  @returns Speed of the Tram.
*/
  int getSpeed();

/**
  Getter for the start Station of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  @note ENSURE(validStringAttribute(_startStation), "Start station must be valid");
  @returns Start Station name of the Tram.
*/
  string getStartStation();

/**
  Getter for the current Station name of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  @note ENSURE(validStringAttribute(_currentStation), "Current station must be valid");
  @returns Name of the current Station the tram is at.
*/
  string getCurrentStation();

/**
  Getter for the Tram direction.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getDirection");
  @note ENSURE(validDirection(_direction), "Tram direction must be either backward or forward");
  @returns The direction the tram is travelling at.
*/
  TramDirection getDirection();

/**
  Setter for the line of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  @note ENSURE(validIntegerAttribute(_line), "The number of a line is negative");
  @param line Line of the Tram.
*/
  void setLine(int line);

/**
  Setter for the capacity of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCapacity");
  @note ENSURE(validIntegerAttribute(_capacity), "Tram capacity is negative");
  @param capacity Capacity of the Tram.
*/
  void setCapacity(int capacity);

/**
  Setter for the speed of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  @note ENSURE(validIntegerAttribute(_speed), "Tram speed is negative");
  @param speed Speed of the Tram.
*/
  void setSpeed(int speed);

/**
  Setter for the start Station name.
 @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
 @note ENSURE(validStringAttribute(_startStation), "Tram start station is empty");
 @param startStaton Start Station name of the Tram.
*/
  void setStartStation(string startStation);

/**
  Setter for the current start Station name.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  @note ENSURE(validStringAttribute(_currentStation), "Tram current station is empty");
  @param station Start Station name.
*/
  void setCurrentStation(string station);

/**
  Switches the direction of the Tram. E.g. Forward becomes Backward, and viceversa.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling switchDirection");
  @note ENSURE(validDirection(_direction), "Tram direction must be valid");
*/
  void switchDirection();

 private:
  int _line;
  int _capacity;
  int _speed;
  string _startStation;
  string _currentStation;
  TramDirection _direction;
};

#endif //UNTITLED_TRAM_H

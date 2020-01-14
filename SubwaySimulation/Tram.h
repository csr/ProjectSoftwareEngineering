//============================================================================
// Name        : Tram.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This file holds the header for the Tram class.
//============================================================================

#ifndef UNTITLED_TRAM_H
#define UNTITLED_TRAM_H

#include "Station.h"

using namespace std;

enum TramType {Albatross, PCC};

class Tram {
 public:


/**
 Constructs a Tram class with line, capacity, speed, and start Station name.
 @note ENSURE(line == getLine(), "Line wasn't set correctly in constructor");
 @note ENSURE(type == getType(), "Type wasn't set correctly in constructor");
 @note ENSURE(startStation == getCurrentStationName(), "Start station wasn't set correctly in constructor");
 @note ENSURE(number == getNumber(), "Number wasn't set correctly in constructor");
 @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 @param line Line of the Tram.
 @param type Type of the Tram.
 @param startStation Start Station of the Tram.
 @param number Number of Vehicle of the Tram
 @returns An instance of Tram
*/
  Tram(int line, TramType type, string startStation, int number);

  bool properlyInitialized();

/**
  Getter for the line of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  @returns Line of the Tram.
*/
  int getLine();

/**
  Getter for the maximum capacity of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getMaxCapacity");
  @returns Capacity of the Tram.
*/
  virtual int getMaxCapacity() = 0;

/**
  Getter for the current capacity of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentCapacity");
  @returns Capacity of the Tram.
*/
  int getCurrentCapacity();

/**
  Getter for the speed of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  @returns Speed of the Tram.
*/
  int getSpeed();

/**
  Getter for the current Station of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  @returns Current Station the tram is at.
*/
  Station* getCurrentStation();

/**
  Getter for the current Station name of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStationName");
  @return Current Station Name the tram is at.
*/
  string getCurrentStationName();

/**
  Getter for the type of the Tram.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getType");
  @return Type of the tram
*/
  TramType getType();

/**
  Getter for the number of Vehicle of Tram
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getVehicle");
  @return Vehicle number of the tram
*/
  int getVehicle();

/**
  Setter for the current Station.
  @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  @note ENSURE(ValidStringAttribute(getCurrentStation()), "Tram current station must be valid");
  @note ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
  @param station Start Station.
*/
  void setCurrentStation(Station *station);

  /**
   * Setter for the current station Name
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStationName");
   * @note ENSURE(getCurrentStationName() == currentStation, "Tram start station name was not set correctly");
   * @param station: name of Station
   */
  void setCurrentStationName(string station);

  /**
   * Setter for currentCapacity attribute of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentCapacity");
   * @note ENSURE(getCurrentCapacity() <= getMaxCapacity(), "Tram currentCapacity is greater than maximum capacity");
   * @note ENSURE(number == getCurrentCapacity(), "Tram currentCapacity was not set correctly");
   * @param number: number of current passengers on Tram
   */
  void setCurrentCapacity(int number);

  /**
 * Moves the tram.
 * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentCapacity");
 * @note ENSURE(ValidIntegerAttribute(time), "Time must be zero or positive");
 * @param simulation time
 * @param outputStream Output Stream
 * @param statsFile CSV file
 */

  void move(int time, ostream &outputStream, ostream &statsFile);

 private:
  Tram* _initCheck;
  int _number;
  int _line;
  Station* _currentStation;
  string _currentStationName;
  TramType _type;
  int _currentCapacity;
  int _maxCapacity;
  int _turnover;
  int _speed;
  int _distance;
  int _waitingTime;

  void setSpeed();

  virtual Station* getNextStation() = 0;
  virtual bool trackFree() = 0;
  virtual int calculateDistance() = 0;
  void arriveToStation();
  void leaveStation();

  void printCSVData(int time, bool isLeaving, ostream &statsStream);
};

#endif //UNTITLED_TRAM_H

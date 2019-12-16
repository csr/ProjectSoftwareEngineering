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
<<<<<<< HEAD
 @param startStation Start Station of the Tram.
 @param number Number of Vehicle of the Tram
 @returns An instance of Tram
=======
 @param startStation Start station of the Tram.
 @param number Tram number.
 @returns An instance of Tram.
>>>>>>> c1ced59c2309cd6c487b76772db759a297145a97
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
  int getMaxCapacity();

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
   * Getter for the current Station name of the Tram.
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStationName");
   * @return Current Station Name the tram is at.
   */
  string getCurrentStationName();

  /**
   * Getter for the type of the Tram.
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getType");
   * @return Type of the tram
   */
  TramType getType();

  /**
   * Getter for the number of Vehicle of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getVehicle");
   * @return Vehicle number of the tram
   */
  int getVehicle();

  /**
   * Getter for the waiting time in a station of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getWaiting");
   * @return Waiting number of the Tram
   */
  int getWaiting();

  /**
   * Getter for the Turnover of the Tram.
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getTurnover");
   * @return Turnover number of the Tram
   */
  int getTurnover();

  /**
   * Getter for the next station of the Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getNextStation");
   * @return Next station of the Tram to set as a new current Station
   */
  Station* getNextStation();

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
   * Setter for turnover attribute of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setTurnover");
   * @note ENSURE(getTurnover() == 2 * getCurrentCapacity(), "Tram doesn't initialize in a good way turnover attribute");
   */
  void setTurnover();

  /**
   * Setter for speed attribute of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
   * @note ENSURE(getTurnover() == previous + 2 * getCurrentCapacity(), "Tram doesn't initialize in a good way turnover attribute");
   */
  void setSpeed();

  /**
   * Setter for Waiting attribute of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setWaiting");
   * @note ENSURE(this->getWaiting() == number && number >= 0, "Tram does't set waiting time");
   * @param number: number of waiting tick
   */
  void setWaiting(int number);

  /**
   * Setter for Distance attribute of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setDistance");
   * @note ENSURE(distance == this->getDistance(), "Distance wasn't set");
   * @param distance: number of distance
   */
  void setDistance(int distance);

  /**
   * Leave action that makes a tram start to move to next Station
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling leave");
   * @note ENSURE(!this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't leave the station");
   */
  void leave();

  /**
   * Arrive action that makes a tram to arrive to next Station
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling arrive");
   * @note ENSURE(this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't arrive in the station");
   */
  void arrive();

  /**
   * Calculate distance from current station to next station.
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling calculateDistance");
   * @note ENSURE(distance > 0, "Distance can't be negative or null");
   */
  int calculateDistance();

  /**
   * Estabilish if the track is free and a tram can move
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling trackFree");
   * @return answer
   */
  bool trackFree();

  /**
   * Decrease by one the distance of a tram from the next station
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling decreaseDistance");
   * @note ENSURE(this->getDistance() == previousDistance - 1, "Tram doesn't decrease the distance");
   */
  void decreaseDistance();

  /**
   * Getter for the distance attribute of Tram
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getDistance");
   * @return distance value of the tram
   */
  int getDistance();

  /**
   * Decrease by one the waiting time on a station
   * @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling decreaseWaiting");
   * @note ENSURE(this->getWaiting() == (previous - 1), "Tram doesn't decrease waiting time");
   */
  void decreaseWaiting();





 private:
  Tram* _initCheck;
  int _number;
  int _line;
  Station* _startStation;
  Station* _currentStation;
  string _currentStationName;
  TramType _type;
  int _currentCapacity;
  int _maxCapacity;
  int _turnover;
  int _speed;
  int _distance;
  int _waiting;

  void setType(TramType type);
  void setMaximumCapacity();
};

#endif //UNTITLED_TRAM_H

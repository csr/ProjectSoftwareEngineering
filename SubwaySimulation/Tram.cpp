//============================================================================
// Name        : Track.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include "Tram.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

Tram::Tram(int line, TramType type, string startStation, int number) {
  _initCheck = this;
  setLine(line);
  setStartStationName(startStation);
  setType(type);
  setNumber(number);
  ENSURE(line == getLine(), "Line wasn't set correctly in constructor");
  ENSURE(startStation == getStartStationName(), "Start station wasn't set correctly in constructor");
}

bool Tram::properlyInitialized() {
  return _initCheck == this;
}

int Tram::getLine() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
  return _line;
}

int Tram::getMaxCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
  return _maxCapacity;
}

int Tram::getSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  return _speed;
}

Station* Tram::getStartStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  return _startStation;
}

Station* Tram::getCurrentStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  return _currentStation;
}

string Tram::getStartStationName() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStationName");
  return _startStationName;
}

TramType Tram::getType() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getType");
  return _type;
}

int Tram::getNumber() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getNumber");
  return _number;
}

void Tram::setLine(int line) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  _line = line;
  ENSURE(ValidIntegerAttribute(getLine()), "Tram line can't be negative");
  ENSURE(line == getLine(), "Tram line was not set correctly");
}

void Tram::setStartStation(Station *startStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
  _startStation = startStation;
  ENSURE(startStation == getStartStation(), "Tram start station was not set correctly");
}

void Tram::setCurrentStation(Station *station) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  _currentStation = station;
  ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
}

void Tram::setStartStationName(string startStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  _startStationName = startStation;
  ENSURE(startStation == getStartStationName(), "Tram start station name was not set correctly");
}

void Tram::setType(TramType type) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setType");
  _type = type;
  ENSURE(type == getType(), "Tram type was not set correctly");
}

void Tram::setNumber(int number) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setTrack");
  _number = number;
  ENSURE(number == getNumber(), "Tram vehicleNumber was not set correctly");
}

void Tram::move() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");

  //Arrive in a new Station
  if(this->getDistance() == 0) {
      Station *currentStation = this->getCurrentStation();
      Track *track = currentStation->getTrack(this->getNumber());
      Station *nextStation = track->getNext();
      this->setCurrentStation(nextStation);
      this->getCurrentStation()->setOccupied(true);
      ENSURE(this->getCurrentStation()->isCurrentlyOccupied(), "Tram doesn't arrive in the next station");
      int passengers = GenerateRandomNumber(0, this->getCurrentCapacity());
      setCurrentCapacity(passengers);
      setTurnover();
      }else {
      //Leave a station
      int passengers = GenerateRandomNumber(this->getCurrentCapacity(), this->getMaxCapacity());
      setCurrentCapacity(passengers);
      setTurnover();
      this->getCurrentStation()->setOccupied(false);

      ENSURE(!this->getCurrentStation()->isCurrentlyOccupied(), "Tram doesn't leave the station");
  }
}

void Tram::setCurrentCapacity(int number) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
  _currentCapacity = number;
  ENSURE(getCurrentCapacity() <= getMaxCapacity(), "Tram currentCapacity is greater than maximum capacity");
  ENSURE(number == getCurrentCapacity(), "Tram currentCapacity was not set correctly");
}

int Tram::getTurnover() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getTurnover");
  return _turnover;
}

void Tram::setTurnover() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setTurnover");
  _turnover = 2 * getCurrentCapacity();
}

void Tram::setSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  if(this->_type == Albatross) {
    _speed = 70;
  } else if (this->_type == PCC) {
    _speed = 40;
  }
}

int Tram::getCurrentCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentCapacity");
  return _currentCapacity;
}

int Tram::getDistance() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getDistance");
  return _distance;
}

int Tram::calculateDistance() {
    REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling calculateDistance");
    int distance = 7200 / _speed;
    if(this->getType() == Albatross && this->getCurrentStation()->getTrack(this->getNumber())->getNext()->getType() != TypeStop){
        distance++;
        ENSURE(distance >= 0, "Distance can not be negative");
        return distance++ + calculateDistance();
    }
    else{
        distance += 60;
        //ENSURE(distance >= 0, "Distance can not be negative");
    }
    return distance;
}
void Tram::setDistance(int distance) {
    REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setDistance");
    _distance = distance;
    ENSURE(distance == this->getDistance(), "Distance wasn't set");
}

void Tram::decreaseDistance() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling decreaseDistance");
  int previousDistance = this->getDistance();
  _distance--;
  ENSURE(this->getDistance() == previousDistance - 1, "Tram doesn't decrease the distance");
}


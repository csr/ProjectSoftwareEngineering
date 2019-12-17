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
  _line = line;
  _type = type;
  _number = number;
  _turnover = 0;
  setCurrentStationName(startStation);

  if(this->_type == Albatross) {
    _maxCapacity = 72;
  } else if (this->_type == PCC) {
    _maxCapacity = 16;
  }

  setCurrentCapacity(0);
  setSpeed();
  setDistance(0);
  setWaiting(0);

  ENSURE(line == getLine(), "Line wasn't set correctly in constructor");
  ENSURE(type == getType(), "Type wasn't set correctly in constructor");
  ENSURE(number == getVehicle(), "Number wasn't set correctly in constructor");
  ENSURE(startStation == getCurrentStationName(), "Start station wasn't set correctly in constructor");
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
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

Station* Tram::getCurrentStation() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  return _currentStation;
}

string Tram::getCurrentStationName() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStationName");
  return _currentStationName;
}

TramType Tram::getType() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getType");
  return _type;
}

int Tram::getVehicle() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getVehicle");
  return _number;
}

int Tram::getWaiting() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getWaiting");
  return _waiting;
}

int Tram::getTurnover() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getTurnover");
  return _turnover;
}

int Tram::getCurrentCapacity() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentCapacity");
  return _currentCapacity;
}

int Tram::getDistance() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getDistance");
  return _distance;
}

void Tram::setCurrentStation(Station *station) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  _currentStation = station;
  _currentStation->getTrack(this->getLine())->setOccupied(true);
  setCurrentStationName(station->getName());
  ENSURE(station->getTrack(this->getLine())->isCurrentlyOccupied(), "Station must be set to occupied");
  ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
}

void Tram::setCurrentStationName(string currentStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  _currentStationName = currentStation;
  ENSURE(getCurrentStationName() == currentStation, "Tram start station name was not set correctly");
}

void Tram::arrive() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling arrive");
  Station* currentStation = this->getCurrentStation();
  Track *track = currentStation->getTrack(this->getLine());
  Station* nextStation = getNextStation();
  this->setCurrentStation(nextStation);
  this->getCurrentStation()->getTrack(this->getLine())->setOccupied(true);

  int randomNumber = GenerateRandomNumber(0, this->getCurrentCapacity());
  setCurrentCapacity(getCurrentCapacity()-randomNumber);
//  cout << "ARRIVING. Current cap: " << ToString(this->getCurrentCapacity())
//       << " max cap: " << ToString(getMaxCapacity())
//       << ", random decrease: " << ToString(randomNumber) << endl;

  ENSURE(this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't arrive in the next station");
}

void Tram::leave() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling leave");

  int randomIncrease = GenerateRandomNumber(this->getCurrentCapacity(), this->getMaxCapacity());

//  cout << "LEAVING. Current cap: " << ToString(this->getCurrentCapacity())
//       << " max cap: " << ToString(getMaxCapacity())
//       << ", random increase: " << ToString(randomIncrease) << endl;

  setCurrentCapacity(randomIncrease);

  updateTurnover();
  setDistance(calculateDistance());
  setWaiting(60);
  this->getCurrentStation()->getTrack(this->getLine())->setOccupied(false);
  ENSURE(!this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't leave the station");
}

void Tram::setCurrentCapacity(int number) {
//  cout << "Setting capacity to: " << ToString(number) << endl;
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
  _currentCapacity = number;
  ENSURE(getCurrentCapacity() <= getMaxCapacity(), "Tram currentCapacity can't be greater than maximum capacity");
//  ENSURE(getCurrentCapacity() >= 0, "Tram currentCapacity must be positive");
  ENSURE(number == getCurrentCapacity(), "Tram currentCapacity was not set correctly");
}

void Tram::updateTurnover() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling updateTurnover");
  int previous = getTurnover();
  _turnover += 2 * getCurrentCapacity();
  ENSURE(getTurnover() == previous + 2 * getCurrentCapacity(), "Tram doesn't initialize in a good way turnover attribute");
}

void Tram::setSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
  if(this->_type == Albatross) {
    _speed = 70;
  } else if (this->_type == PCC) {
    _speed = 40;
  }
}

int Tram::calculateDistance() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling calculateDistance");
  int distance = 7200 / getSpeed();
  if(this->getType() == Albatross){
    distance++;
    ENSURE(distance >= 0, "Distance can not be negative");
    Station* elem = this->getCurrentStation()->getTrack(this->getLine())->getNext();
    while(elem->getType() == TypeStop){
      distance += 7200 / _speed  + 1;
      elem = elem->getTrack(this->getLine())->getNext();
    }
  }
  ENSURE(distance > 0, "Distance can't be negative or null");
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

bool Tram::trackFree() {
  int track = this->getLine();

  if (this->getType() == Albatross){
    bool answer = true;
    Station* elem = this->getCurrentStation()->getTrack(track)->getNext();
    while(elem->getType() == TypeStop){
      if(elem->getTrack(track)->isCurrentlyOccupied())
        return false;
      elem = elem->getTrack(track)->getNext();

    }
    if (elem == this->getCurrentStation())
      return true;
    return !elem->getTrack(track)->isCurrentlyOccupied();
  } else{
    return !this->getCurrentStation()->getTrack(track)->getNext()->getTrack(track)->isCurrentlyOccupied();
  }
}

void Tram::setWaiting(int number) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setWaiting");
  _waiting = number;
  ENSURE(this->getWaiting() == number && number >= 0, "Tram does't set waiting time");
}

void Tram::decreaseWaiting() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling decreaseWaiting");
  int previous = _waiting;
  _waiting = _waiting - 1;
  ENSURE(this->getWaiting() == (previous - 1), "Tram doesn't decrease waiting time");
}

Station* Tram::getNextStation(){
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getNextStation");

  Station* next = this->getCurrentStation()->getTrack(this->getLine())->getNext();
  if (this->getType() == Albatross){
    while(next->getType() == TypeStop){
      next = next->getTrack(this->getLine())->getNext();
    }
  }
  return next;

}

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
  setCurrentStationName(startStation);
  _type = type;
  setNumber(number);

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
  ENSURE(startStation == getCurrentStationName(), "Start station wasn't set correctly in constructor");
  ENSURE(type == getType(), "Type wasn't set correctly in constructor");
  ENSURE(number == getVehicle(), "Number wasn't set correctly in constructor");
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

void Tram::setLine(int line) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
  _line = line;
  ENSURE(ValidIntegerAttribute(getLine()), "Tram line can't be negative");
  ENSURE(line == getLine(), "Tram line was not set correctly");
}

void Tram::setCurrentStation(Station *station) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  _currentStation = station;
  _currentStation->getTrack(this->getLine())->setOccupied(true);
  ENSURE(station->getTrack(this->getLine())->isCurrentlyOccupied() == true, "Station must be set to occupied");
  ENSURE(station == getCurrentStation(), "Tram current station was not set correctly");
}

void Tram::setCurrentStationName(string currentStation) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
  _currentStationName = currentStation;
  ENSURE(getCurrentStationName() == currentStation, "Tram start station name was not set correctly");
}

void Tram::setNumber(int number) {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setTrack");
  _number = number;
  ENSURE(number == getVehicle(), "Tram vehicleNumber was not set correctly");
}

void Tram::arrive(){
    REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
    Station* currentStation = this->getCurrentStation();
    Track *track = currentStation->getTrack(this->getLine());
    Station* nextStation = getNextStation();
    this->setCurrentStation(nextStation);
    this->getCurrentStation()->getTrack(this->getLine())->setOccupied(true);

    ENSURE(this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't arrive in the next station");
    setCurrentCapacity(GenerateRandomNumber(0, this->getCurrentCapacity()));
    setTurnover();
}
void Tram::leave() {
    REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling move");
    setCurrentCapacity(GenerateRandomNumber(this->getCurrentCapacity(), this->getMaxCapacity()));
    setTurnover();
    cout << "New Distance" << calculateDistance() << endl;
    setDistance(calculateDistance());
    setWaiting(60);
    this->getCurrentStation()->getTrack(this->getLine())->setOccupied(false);
    ENSURE(!this->getCurrentStation()->getTrack(this->getLine())->isCurrentlyOccupied(), "Tram doesn't leave the station");
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
    if(this->getType() == Albatross){
        distance++;
        ENSURE(distance >= 0, "Distance can not be negative");
        Station* elem = this->getCurrentStation()->getTrack(this->getLine())->getNext();
        while(elem->getType() == TypeStop){
            distance += 7200 / _speed  + 1;
            elem = elem->getTrack(this->getLine())->getNext();
        }
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

int Tram::getWaiting() {
    REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getWaiting");
    return _waiting;
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
    Station* next = this->getCurrentStation()->getTrack(this->getLine())->getNext();
    if (this->getType() == Albatross){
        while(next->getType() == TypeStop){
            next = next->getTrack(this->getLine())->getNext();
        }
    }
    return next;
}
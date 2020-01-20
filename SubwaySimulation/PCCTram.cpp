//
// Created by bigboss98 on 29/12/19.
//

#include "PCCTram.h"
#include "Tram.h"
#include "DesignByContract.h"


PCCTram::PCCTram(int line, string startStation, int number): Tram(line, PCC, startStation, number) {
}

int PCCTram::calculateDistance() {
  return 7200 / getSpeed();
}

bool PCCTram::trackFree() {
  int track = this->getLine();
  return !this->getCurrentStation()->getTrack(track)->getNext()->getTrack(track)->isCurrentlyOccupied();
}

Station* PCCTram::getNextStation() {
  REQUIRE(this->properlyInitialized(), "PCC wasn't initialized when calling getNextStation");
  return this->getCurrentStation()->getTrack(this->getLine())->getNext();
}

int PCCTram::getMaxCapacity(){
  REQUIRE(this->properlyInitialized(), "PCC wasn't initialized when calling getMaxCapacity");
  return _capacity;
}

int PCCTram::getSpeed() {
  REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
  return _speed;
}
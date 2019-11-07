//============================================================================
// Name        : Tram.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This class is the blueprint for the Tram object.
//============================================================================

#include "Tram.h"

int Tram::getLine() const {
  return line;
}

int Tram::getCapacity() const {
  return capacity;
}

int Tram::getSpeed() const {
  return speed;
}

const string &Tram::getStartStation() const {
  return startStation;
}

void Tram::setLine(int line) {
  Tram::line = line;
}

void Tram::setCapacity(int capacity) {
  Tram::capacity = capacity;
}

void Tram::setSpeed(int speed) {
  Tram::speed = speed;
}

void Tram::setStartStation(const string &startStation) {
  Tram::startStation = startStation;
}
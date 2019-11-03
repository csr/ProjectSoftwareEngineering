//
// Created by veror on 03/11/2019.
//

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

//
// Created by veror on 28/10/2019.
//

#include "TokenTram.h"
using std::string;

int TokenTram::getLine() const {
    return line;
}

int TokenTram::getCapacity() const {
    return capacity;
}

int TokenTram::getSpeed() const {
    return speed;
}

string TokenTram::getStartStation() {
    return startStation;
}

void TokenTram::setLine(int line) {
    TokenTram::line = line;
}

void TokenTram::setCapacity(int capacity) {
    TokenTram::capacity = capacity;
}

void TokenTram::setSpeed(int speed) {
    TokenTram::speed = speed;
}

void TokenTram::setStartStation(string startStation) {
    TokenTram::startStation = startStation;
}

TokenTram::TokenTram(int line, int capacity, int speed, string startStation) : line(line), capacity(capacity),
                                                                               speed(speed),
                                                                               startStation(startStation) {}

//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>

#include "Station.h"
#include "Tram.h"
#include "Subway.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

using namespace std;

Subway::Subway() {
    _initCheck = this;

    // Import empty station and tram arrays
    importData({}, {});

    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
    ENSURE(getTramsCount() == 0, "default constructor should return build empty subway");
    ENSURE(getStationsCount() == 0, "default constructor should return build empty subway");
}

bool Subway::properlyInitialized() {
    return _initCheck == this;
}

void Subway::importData(vector<Station *> stations, vector<Tram *> trams) {
    REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling importData");
    _stationsArray = stations;
    _tramsArray = trams;

    // Fill stations map
    for (auto station : _stationsArray) {
        _stationsMap[station->getName()] = station;
    }

    // Fill trams map
    for (auto tram : _tramsArray) {
        _tramsMap[tram->getLine()] = tram;
    }
    ENSURE(this->getTramsCount() >= 0, "Trams number are negative");
    ENSURE(this->getStationsCount() >= 0, "Stations number are negative");
}

int Subway::getTramsCount() {
    REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
    unsigned long size = _tramsMap.size();
    // TO CHECK - get this checked by Prof. Brent
    ENSURE(ValidIntegerAttribute(size), "Trams count can't be negative");
    return size;
}

int Subway::getStationsCount() {
    REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
    unsigned long size = _stationsMap.size();
    // TO CHECK - get this checked by Prof. Brent
    ENSURE(ValidIntegerAttribute(size), "Stations count can't be negative");
    return size;
}

string Subway::toString() {
    REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");

    string outputString;
    for (auto &station : this->_stationsArray) {
        outputString = outputString + "Station " + station->getName() + "\n" +
                       "<- Station " + station->getPrevious()->getName() + "\n" +
                       "-> Station " + station->getNext()->getName() + "\n" +
                       "Track " + to_string(station->getTrack());

        // If there's a tram associated to the track, print capacity
        if (this->_tramsMap.count(station->getTrack())) {
            Tram *tram = this->_tramsMap[station->getTrack()];
            if (tram->getStartStation()->getName() == station->getName()) {
                outputString = outputString + ": Tram with " + to_string(tram->getMaxCapacity()) + " seats";
            }
        }
        outputString += "\n";
    }
    return outputString;
}

vector<Station*> Subway::getStations(){
    return _stationsArray;
}

void Subway::reset() {
    REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling reset");
    _stationsArray.clear();
    _tramsArray.clear();
    _stationsMap.clear();
    _tramsMap.clear();
    ENSURE(this->getTramsCount() == 0, "Trams array must be cleared");
    ENSURE(this->getStationsCount() == 0, "Stations map must be cleared");
}

void Subway::computeAutomaticSimulation(int steps, ostream &outputStream) {
    REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
    REQUIRE(steps >= 0, "Number of steps must be positive");
    int current = 0;
    while (current < steps) {
        collectStatisticalData();
        this->moveTramsOnce(outputStream);
        current++;
    }
}

void Subway::moveTramsOnce(ostream &outputStream) {
    REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
    for (auto tram : this->_tramsArray) {
        string previousStationName = tram->getCurrentStation()->getName();
        if(!tram->getCurrentStation()->getNext()->isOccupy())
            tram->move();

        string currentStationName = tram->getCurrentStation()->getName();
        outputStream << "Tram " << tram->getLine() << " moved from station " << previousStationName <<
                     " to station " << currentStationName << endl;
    }
}

void Subway::collectStatisticalData(){
//    fileStream <<
}


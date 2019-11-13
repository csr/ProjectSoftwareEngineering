//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <unordered_map>

#include "tinyxml.h"
#include "Station.h"
#include "Tram.h"

#include "Subway.h"
#include "DesignByContract.h"

using namespace std;

Subway::Subway() {
  _initCheck = this;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Subway::properlyInitialized() {
  return _initCheck == this;
}

void Subway::addStationsTrams(unordered_map<string, Station*> stations, unordered_map<int, Tram*> trams) {
  this->stations = stations;
  this->trams = trams;
}

void Subway::addStations(vector<Station*> stations) {
  this->stationsArray = stations;
}

void Subway::addStation(Station *station) {
  stations[station->getName()] = station;
}

void Subway::addTram(Tram *tram) {
  trams[tram->getLine()] = tram;
}

int Subway::getTramsCount() {
 return trams.size();
}

int Subway::getStationsCount() {
  return stations.size();
}

string Subway::toString() {
    string out = "";
    for (auto & station : this->stationsArray) {
        out = out + "Station " + station->getName() + "\n" +
             "<- Station " + station->getPrevious() + "\n" +
             "-> Station " + station->getNext() + "\n" +
             "Track " + to_string(station->getTrack()) + "\n";
        // If there's a tram associated to the track, print capacity
        if (this->trams.count(station->getTrack())) {
            Tram *tram = this->trams[station->getTrack()];
            if (tram->getStartStation() == station->getName()) {
                out = out + ": Tram with " + to_string(tram->getCapacity()) + " seats";
            }
        }
    }
    return out;
}
// Simulation
void Subway::computeSimulation(int steps) {
}

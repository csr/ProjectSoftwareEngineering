//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include "tinyxml.h"
#include "Station.h"
#include "Tram.h"

#include "Subway.h"
#include "DesignByContract.h"

using namespace std;

Subway::Subway() {

}

void Subway::addStation(Station station) {
  stations[station.getName()] = station;
}

void Subway::addTram(Tram tram) {
  trams[tram.getLine()] = tram;
}

int Subway::getTramsCount() {
 return trams.size();
}

int Subway::getStationsCount() {
  return stations.size();
}

// Simulation
void Subway::computeSimulation(int steps) {
}


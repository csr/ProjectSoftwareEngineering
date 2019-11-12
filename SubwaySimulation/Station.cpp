//============================================================================
// Name        : Station.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This class is the blueprint for the Station object.
//============================================================================

#include <iostream>
#include "Station.h"

using namespace std;

Station::Station() {
}

Station::Station(string name, string nextStation, string previousStation, int track) {
  // TODO: properly initialized?
  setName(name);
  setNext(nextStation);
  setPrevious(previousStation);
  setTrack(track);
}

const string &Station::getName() const {
  return name;
}

const string &Station::getNext() const {
  return next;
}

const string &Station::getPrevious() const {
  return previous;
}

int Station::getTrack() const {
  return track;
}

void Station::setName(const string &name) {
  Station::name = name;
}

void Station::setNext(const string &next) {
  Station::next = next;
}

void Station::setPrevious(const string &previous) {
  Station::previous = previous;
}

void Station::setTrack(int track) {
  Station::track = track;
}

string toString() {
//  cout << "Station " << Station::name << endl;
//  cout << "<- " << "Station " << previous << endl;
//  cout << "-> " << "Station" << next << endl;
  return "Hello";
}
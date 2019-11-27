//============================================================================
// Name        : Station.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#ifndef UNTITLED_STATION_H
#define UNTITLED_STATION_H
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>

#include "Track.h"

using namespace std;

enum StationType {TypeStation, TypeStop};

//<name>C</name>
//<TRACK>...</TRACK>
//<TRACK>...</TRACK>
//<type>stop</type>

class Track;

class Station {
 public:
  Station(string name, string nextStation, string previousStation, StationType type);

  bool properlyInitialized();

  void setName(string name);

  void setOccupied(bool isOccupied);

  string getName();

  StationType getType();

  Track* getTrack(int number);

  vector<Track*> getTracks();

  bool isCurrentlyOccupied();

 private:
  Station * _initCheck;
  string _name;
  StationType _type;
  bool _isOccupied;
  unordered_map<int, Track*> _tracks;
};

#endif //UNTITLED_STATION_H

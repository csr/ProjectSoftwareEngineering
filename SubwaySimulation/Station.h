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

class Track;

class Station {
 public:
  Station(string name, StationType type, unordered_map<int, Track*> tracks);

  bool properlyInitialized();

  void setName(string name);

  void setOccupied(bool isOccupied);

  void setTracks(unordered_map<int, Track*> tracks);

  string getName();

  StationType getType();

  Track* getTrack(int number);

  unordered_map<int, Track*> getTracks();

  vector<Track*> getTracksArray();

  bool isCurrentlyOccupied();

 private:
  Station * _initCheck;
  string _name;
  StationType _type;
  bool _isOccupied;
  map<int, Track*> _tracks;
};

#endif //UNTITLED_STATION_H

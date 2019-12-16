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
#include "SubwaySimulationUtils.h"

using namespace std;

enum StationType {NotSet, TypeStation, TypeStop};

class Track;

class Station {
 public:
  Station(string name, StationType type, unordered_map<int, Track*> tracks);

  bool properlyInitialized();

  void setTracks(unordered_map<int, Track*> tracks);

  string getName();

  StationType getType();

  Track* getTrack(int number);

  unordered_map<int, Track*> getTracks();

  vector<Track*> getTracksArray();


 private:
  Station * _initCheck;
  string _name;
  StationType _type;
  unordered_map<int, Track*> _tracks;
};

#endif //UNTITLED_STATION_H

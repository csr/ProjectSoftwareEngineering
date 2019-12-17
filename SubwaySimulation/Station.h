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
 
 /**
     * Constructs a Station class with name, type, track.
     *@note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     * @param name
     * @param type
     * @param tracks
     */
  Station(string name, StationType type, unordered_map<int, Track*> tracks);

  bool properlyInitialized();

 /**
   * Setter for the tracks of the Station
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTracks");
   * ENSURE(tracks == getTracks(), "Station tracks weren't set correctly");
   * @param tracks of the Station
   */
  void setTracks(unordered_map<int, Track*> tracks);

 /**
   * Getter for the name of  the Station
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getName");
   * @return Name of the Station
   */
  string getName();

 /**
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getType");
   * @return Type of the Station
   */
  StationType getType();

 /**
   * Getter for the Track of the Station with number equal to number
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");
   * @param number of the required track of the Station
   * @return Track of the Station corresponding to number
   */
  Track* getTrack(int number);

 /**
   * Getter for all the Tracks of the Station
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTracks");
   * @return map of Tracks of the Station
   */
  unordered_map<int, Track*> getTracks();

 /**
   * Getter for all the Tracks of the Station
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTracksArray");
   * @return vector of Tracks of the Station
   */
  vector<Track*> getTracksArray();


 private:
  Station * _initCheck;
  string _name;
  StationType _type;
  unordered_map<int, Track*> _tracks;
};

#endif //UNTITLED_STATION_H

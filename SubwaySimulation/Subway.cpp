//============================================================================
// Name        : Subway.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <iostream>
#include <fstream>

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
  resetCurrentTime();
  ENSURE(getTramsCount() == 0, "Trams count must be initially zero");
  ENSURE(getStationsCount() == 0, "Stations count must be initially zero");
  ENSURE(getCurrentTime() == 0, "Current time must be initially zero");
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
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
    _tramsMap[make_pair(tram->getLine(), tram->getVehicle())] = tram;
    int track = tram->getLine();
    tram->getCurrentStation()->getTrack(track)->setOccupied(true);
  }
  ENSURE(this->getTramsCount() >= 0, "Trams number are negative");
  ENSURE(this->getStationsCount() >= 0, "Stations number are negative");
}

int Subway::getTramsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTramsCount");
  unsigned long size = _tramsMap.size();
  ENSURE(ValidIntegerAttribute(size), "Trams count can't be negative");
  return size;
}

int Subway::getStationsCount() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStationsCount");
  unsigned long size = _stationsMap.size();
  ENSURE(ValidIntegerAttribute(size), "Stations count can't be negative");
  return size;
}

string Subway::toString() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling toString");

  string outputString;

  for (auto &station : this->_stationsArray) {
    outputString += + "Station " + station->getName();

    unordered_map<int, Track*> tracks = station->getTracks();

    // Iterate over tracks and print track details
    for (auto *track : station->getTracksArray()) {
      outputString += "\nTrack " + to_string(track->getTrack()) + "\n" +
          "<- Station " + track->getPrevious()->getName() + "\n" +
          "-> Station " + track->getNext()->getName();

      // Check if there's a tram with same line and station
      for (auto &tram: this->_tramsArray) {
        if (tram->getLine() == track->getTrack() && tram->getCurrentStation()->getName() == station->getName()) {
          outputString += "\nTram with " + to_string(tram->getMaxCapacity()) + " seats";
        }
      }
    }
    outputString += "\n\n";
  }
  return outputString;
}

string Subway::graficalOutput() {

  string outputGrafical = "";
  //cout << "ciaao" << endl;
  map<int, vector<Station *>> tracks; // int = num of track, stations_track = stations in that track
  for (auto station : this->getStations()) {
    vector<Track *> tracks_station = station->getTracksArray(); // tracks of station;
    for (auto track : tracks_station) {
      int num_track = track->getTrack();
      //cout << "numTrack " << num_track << endl;
      if (tracks.find(num_track) == tracks.end()) { // that track is not yet in the map
        //cout << "EEEEEEE" << endl;
        vector<Station *> stations_track;
        stations_track.push_back(station);
        tracks.insert({num_track, stations_track});
        Station *next_station = track->getNext();
        map<int, vector<Station *>>::iterator it = tracks.find(num_track);
        //cout << "NEXT " << next_station->getName() << endl;
        while (next_station->getName() != station->getName()) {
          it->second.push_back(next_station);
          Track* track1 = next_station->getTrack(num_track);
          next_station = track1->getNext();
          //cout << "next station " << next_station->getName() << endl;
          //cout << "station " << station->getName() << endl;
        }
      }
    }
  }

  for (map<int, vector<Station *>>::iterator it = tracks.begin(); it != tracks.end(); ++it) {
    int num_track = it->first;
    string current_station = "";
    for (auto tram : this->getTrams()) {
      if (tram->getLine() == num_track) {
        current_station = tram->getCurrentStationName();
      }
    }
    int n = it->second.size();
    int size_array = n * 2 + n;
    //cout << "sxe " << it->second.size() << endl;
    //cout << "sxe " << size_array << endl;
    outputGrafical += "Track " + to_string(num_track) + ":\n=";
    string array[size_array];
    for (int i = 0; i < size_array; i++) {
      array[i] = " ";
    }
    for (int i = 0; i < it->second.size(); i++) {
      if (i != it->second.size() - 1) {
        outputGrafical += it->second[i]->getName() + "==";
      } else {
        outputGrafical += it->second[i]->getName() + "=\n";
      }
      //cout << "curr " << current_station << endl;
      //cout << "station " << it->second[i]->getName() << endl;
      if (current_station == it->second[i]->getName())
        array[i * 3 + 1] = "T";
    }
    for(int i = 0; i < size_array; i++) {
      outputGrafical += array[i];
    }
    outputGrafical += "\n";
  }

  return outputGrafical;
}

vector<Station*> Subway::getStations() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getStations");
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

void Subway::computeAutomaticSimulation(int steps, ostream &outputStream, ostream& statsStream) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling computeAutomaticSimulation");
  REQUIRE(steps >= 0, "Number of steps must be positive");

  resetCurrentTime();

  statsStream << "Time,Vehicle,Line,Action,Station,Turnover,Capacity" << endl;

  while (getCurrentTime() < steps) {
    this->moveTramsOnce(outputStream, statsStream);
    incrementTime();
  }
}

void Subway::printStatsData(bool isLeaving, Tram *tram, ostream &statsStream) {
  int time = getCurrentTime();
  string arrivingLeavingStr = isLeaving ? "Leaving" : "Arriving";
  Station *currentStation = tram->getCurrentStation();
  string stationName = currentStation->getName();
  int turnover = tram->getTurnover();
  int currentCapacity = tram->getCurrentCapacity();

  statsStream << ConvertSecondsToTimeString(time) << ","
              << tram->getVehicle() << ","
              << tram->getLine() << ","
              << arrivingLeavingStr << ","
              << stationName << ","
              << ToString(turnover) << ","
              << ToString(currentCapacity)
              << endl;
}

void Subway::moveTramsOnce(ostream &outputStream, ostream& statsFile) {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling moveTramsOnce");
  outputStream.flush();
  for (auto tram : this->_tramsArray) {
    Station *currentStation = tram->getCurrentStation();
    string previousStationName = currentStation->getName();
    if (tram->getDistance() == 0) {
      if(tram->getWaiting() == 0) {
        Track *track = currentStation->getTrack(tram->getVehicle());
        if (tram->trackFree()) {
          //Leave a station
          tram->leave();
          printStatsData(true, tram, statsFile);
        }
      }else {
        tram->decreaseWaiting();
      }
    } else if(tram->getDistance() == 1) {
      //Arrive in a Station
      tram->decreaseDistance();
      tram->arrive();
      string currentStationName = tram->getCurrentStation()->getName();
      outputStream << "Tram " << tram->getLine() << " moved from station " << previousStationName <<
                   " to station " << currentStationName << " at time " << ConvertSecondsToTimeString(getCurrentTime()) << endl;
      printStatsData(false, tram, statsFile);
    }else {
      tram->decreaseDistance();
    }
  }
}

void Subway::resetCurrentTime() {
  _time = 0;
}

int Subway::getCurrentTime() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTime");
  ENSURE(_time >= 0, "Time can't be negative");
  return _time;
}

void Subway::incrementTime() {
  int previous = getCurrentTime();
  _time++;
}

vector<Tram*> Subway::getTrams() {
  REQUIRE(this->properlyInitialized(), "Subway wasn't initialized when calling getTracks");
  return _tramsArray;
}

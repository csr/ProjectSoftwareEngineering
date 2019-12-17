//
// Created by bigboss98 on 23/11/19.
//

#include <fstream>
#include "SubwaySimulationExporter.h"
#include "Subway.h"
#include "SubwaySimulationUtils.h"
#include "DesignByContract.h"

SubwaySimulationExporter::SubwaySimulationExporter(Subway *subway) {
  _initCheck = this;
  _subway = subway;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool SubwaySimulationExporter::properlyInitialized() {
  return _initCheck == this;
}

string SubwaySimulationExporter::simpleOutput() {
  REQUIRE(this->properlyInitialized(), "Exporter wasn't initialized when calling toString");

  string outputString;

  for (auto &station : _subway->getStations()) {
    outputString += + "Station " + station->getName();

    unordered_map<int, Track*> tracks = station->getTracks();

    // Iterate over tracks and print track details
    for (auto *track : station->getTracksArray()) {
      outputString += "\nTrack " + to_string(track->getTrack()) + "\n" +
          "<- Station " + track->getPrevious()->getName() + "\n" +
          "-> Station " + track->getNext()->getName();

      // Check if there's a tram with same line and station
      for (auto &tram: _subway->getTrams()) {
        if (tram->getLine() == track->getTrack() && tram->getCurrentStation()->getName() == station->getName()) {
          outputString += "\nTram with " + to_string(tram->getMaxCapacity()) + " seats";
        }
      }
    }
    outputString += "\n\n";
  }
  return outputString;
}

string SubwaySimulationExporter::graficalOutput() {
  REQUIRE(this->properlyInitialized(), "Exporter wasn't initialized when calling toString");

  string outputGrafical = "";
  //cout << "ciaao" << endl;
  map<int, vector<Station *>> tracks; // int = num of track, stations_track = stations in that track
  for (auto station : _subway->getStations()) {
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
    for (auto tram : _subway->getTrams()) {
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
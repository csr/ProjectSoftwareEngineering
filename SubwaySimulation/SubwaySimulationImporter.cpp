//============================================================================
// Name        : SubwaySimulationImporter.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <regex>

#include "SubwaySimulationImporter.h"
#include "SubwaySimulationUtils.h"
#include "Station.h"
#include "Tram.h"
#include "tinyxml.h"
#include "Track.h"

using namespace std;

int minimumStationChildrenCount = 4; // name, track1, track2, trackN (supporting multiple tracks), type
int maxTramChildrenCount = 4; // line, vehicle, type, startStation
int maxTrackChildrenCount = 3; // track, next, previous

enum RootElementType {StationT, TramT, InvalidT};

// Auxiliary function for internal use only
const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
  if (pElement == NULL) return "";

  TiXmlNode *elemNode = pElement->FirstChild();
  if (elemNode == NULL) return "";
  TiXmlText* text = elemNode->ToText();
  if(text == NULL) return "";
  return text->Value();
}

// A type can be either Station, Tram, or Invalid
RootElementType determineRootElementType(string rootName) {
  if (rootName == "STATION") {
    return StationT;
  } else if (rootName == "TRAM") {
    return TramT;
  } else {
    return InvalidT;
  }
}

// Parsing track in another function to make code more modular
Track *parseTrack(TiXmlElement *root, std::ostream& errStream) {
  TiXmlNode *elem_previous, *elem_next, *elem_track;

  elem_next = root->FirstChild("next");
  elem_previous = root->FirstChild("previous");
  elem_track = root->FirstChild("track");

  string next = fetch_text(elem_next, errStream);
  string previous = fetch_text(elem_previous, errStream);
  string trackStr = fetch_text(elem_track, errStream);
  int track = 0;

  if (!ValidStringAttribute(next) || !ValidStringAttribute(previous)) {
    return NULL;
  }

  if (IsStringNumber(trackStr)) {
    track = stoi(trackStr);
  } else {
    return NULL;
  }

  // Check track children count
  int childrenCount = 0;
  for (TiXmlElement *node = root->FirstChildElement(); node; node = node->NextSiblingElement()) {
    childrenCount++;
  }
  if (childrenCount != maxTrackChildrenCount) {
    return NULL;
  }

  return new Track(track, next, previous);
}

// Parse station given its root element
Station *parseStation(TiXmlElement *root, std::ostream& errStream) {
  // Edge case: if the station is empty return null
  if (root->NoChildren()) {
    return NULL;
  }

  // map of future tracks
  unordered_map<int, Track*> tracks;
  StationType typeStation;
  string name;

  int childrenCount = 0;

  for (TiXmlElement *node = root->FirstChildElement(); node; node = node->NextSiblingElement()) {
    childrenCount++;

    // elem_value can be name, type, TRACK
    string elem_value = node->Value();

    // Parse track
    if (elem_value == "TRACK") {
      Track *track = parseTrack(node, errStream);
      if (track != NULL) {
        int number = track->getTrack();
        tracks[number] = track;
      } else {
        return NULL;
      }
    } else if (elem_value == "type") {
      string type = fetch_text(node, errStream);
      // check if the type is correct
      if (type == "station") {
        typeStation = TypeStation;
      } else if (type == "stop") {
        typeStation = TypeStop;
      } else {
        // Invalid station type means invalid station
        return NULL;
      }
    } else if (elem_value == "name") {
      name = fetch_text(node, errStream);
      if (!ValidStringAttribute(name)) {
        return NULL;
      }
    } else {
      // Unrecognized element
      return NULL;
    }
  }

  if (childrenCount < minimumStationChildrenCount) {
    return NULL;
  }

  return new Station(name, typeStation, tracks);
}

// Parse station given its root element
Tram *parseTram(TiXmlElement *root, std::ostream& errStream) {
  // Edge case: if the tram is empty return null
  if (root->NoChildren()) {
    return NULL;
  }

  TramType type;
  string startStation;
  int vehicle = 0, line = 0;

  // Check that the number of children is 4
  int childrenCount = 0;
  for (TiXmlElement *node = root->FirstChildElement(); node; node = node->NextSiblingElement()) {
    childrenCount++;

    string elem_value = node->Value();

    if (elem_value == "line") {
      string lineStr = fetch_text(node, errStream);
      if (IsStringNumber(lineStr)) {
        line = stoi(lineStr);
      } else {
        return NULL;
      }
    } else if (elem_value == "type") {
      string typeStr = fetch_text(node, errStream);
      if (typeStr == "Albatross") {
        type = Albatross;
      } else if (typeStr == "PCC") {
        type = PCC;
      } else {
        return NULL;
      }
    } else if (elem_value == "startStation") {
      startStation = fetch_text(node, errStream);
      if (!ValidStringAttribute(startStation)) {
        return NULL;
      }
    } else if (elem_value == "vehicle") {
      string vehicleStr = fetch_text(node, errStream);
      if (IsStringNumber(vehicleStr)) {
        vehicle = stoi(vehicleStr);
      } else {
        return NULL;
      }
    } else {
      // invalid element found
      return NULL;
    }
  }

  if (childrenCount != maxTramChildrenCount) {
    return NULL;
  }

  return new Tram(line, type, startStation, vehicle);
}

// CONSISTENCY

// auxiliary for check_prev_next_tracks: find next and previous of a station in a particular track
int find_next_prev_station(unordered_map<int, Track*>::iterator ptr, unordered_map<string, Station*> stations) {
    int numTrack = ptr->first;
    Track *track = ptr->second;
    string next = track->getNextStr();
    string prev = track->getPreviousStr();

    // Find next station
    unordered_map<string, Station *>::iterator it1;
    it1 = stations.find(next);
    // Find previous station
    unordered_map<string, Station *>::iterator it2;
    it2 = stations.find(prev);

    return numTrack;
}

// auxiliary for check_prev_next_tracks: check if nextStation, prevStation have same track of station
bool check_same_track(int numTrack, unordered_map<string, Station*>::iterator it1, unordered_map<string, Station*>::iterator it2, bool is_ok) {
    Station *nextStation = it1->second;
    Station *prevStation = it2->second;
    unordered_map<int, Track*> tracksNext = nextStation->getTracks();
    unordered_map<int, Track*> tracksPrev = prevStation->getTracks();

    // check if nextStation has same track among its tracks
    unordered_map<int, Track*>::iterator it3;
    it3 = tracksNext.find(numTrack);
    // check if nextStation has same track among its tracks
    unordered_map<int, Track*>::iterator it4;
    it4 = tracksPrev.find(numTrack);

    if(it3 == tracksNext.end() || it4 == tracksPrev.end()) { // nextStation or prevStation has not same track
        is_ok = false; // return because consistency is not respected
    }

    return is_ok;
}

// check if each station has next and previous on each track with same track
bool check_prev_next_tracks(unordered_map<string, Station*> stations, unordered_map<int, Tram *> trams) {
    bool is_ok = true;
    unordered_map<string, Station *>::iterator it;

    for (it = stations.begin(); it != stations.end() && is_ok; it++) {
        Station *station = it->second;
        string name = station->getName();
        //oppure anche string name = it->first quindi con la key
        unordered_map<int, Track *> tracks = station->getTracks();
        unordered_map<int, Track *>::iterator ptr;
        for (ptr = tracks.begin(); ptr != tracks.end(); ptr++) {
            unordered_map<string, Station *>::iterator it1;
            unordered_map<string, Station *>::iterator it2;
            int numTrack = find_next_prev_station(ptr, stations);
            // Check if element exists in map or not

            if (it1 != stations.end() && it2 != stations.end()) { // station has a valid next and previous
                is_ok = check_same_track(numTrack, it1, it2, is_ok);
                if (is_ok == false) {
                    return is_ok; // return because consistency is not respected
                }
            } else { // station has not a valid next or previous
                is_ok = false;
                return is_ok; // return because consistency is not respected
            }
        }
    }

    return is_ok;
}

// check if startStation of each tram is in stations and if line corresponds to a track in the startStation
bool check_station_tram(map<pairInt, Tram*> trams, unordered_map<string, Station*> stations) {
    bool is_ok = true;
    map<pairInt, Tram*>::iterator it;

    for (it = trams.begin(); it != trams.end() && is_ok; it++) {
        Tram *tram = it->second;
        string startStation = tram->getStartStationName();
        int line = tram->getLine();
        unordered_map<string, Station *>::iterator it1;
        it1 = stations.find(startStation);
        if(it1 != stations.end()) { // stations contains the startStation of the tram
            Station *station = it1->second;
            unordered_map<int, Track*> tracks = station->getTracks();
            unordered_map<int, Track*>::iterator it2;
            it2 = tracks.find(line);
            if(it2 == tracks.end()) {
                is_ok = false;
                return is_ok;
            }
        } else { // stations does not contain the startStation of the tram
            is_ok = false;
            return is_ok;
        }
    }

    return is_ok;
}

// Check if each station has a next and previous with same track and if each track has exactly one tram
// point 2 - 4 of consistency
//bool check_prev_next_track_tram(unordered_map<string, Station*> stations, unordered_map<int, Tram *> trams){
//  bool is_ok = true;
//  unordered_map<string, Station*>::iterator it;
//  for (it = stations.begin(); it != stations.end() && is_ok; it++) {
//    Station *station = it->second;
//    string next = station->getNextName();
//    string prev = station->getPreviousName();
//    int track = station->getTrack();
//
//    // check if each track has exactly one tram: it counts how many trams have line == track
//    // point 4 of consistency
//    if (trams.count(track) == 0) {
//      return false;
//    }
//
//    // iterator for next
//    unordered_map<string, Station*>::iterator it1;
//    // Find next station
//    it1 = stations.find(next);
//    // iterator for previous
//    unordered_map<string, Station*>::iterator it2;
//    // Find previous station
//    it2 = stations.find(prev);
//
//    // Check if element exists in map or not
//    if(it1 != stations.end() && it2 != stations.end()){
////      int next_track = find_track(stations, it1);
////      int prev_track = find_track(stations, it2);
//
//      // TEMPORANEO
//      int next_track = 0;
//      int prev_track = 0;
//
//      if(track == next_track && next_track == prev_track)
//        is_ok =  true;
//      else
//        is_ok = false;
//    }
//    else
//      is_ok = false;
//  }
//  return is_ok;
//}

// Check if each tram has its startStation in the subway and its line corresponds to track of its startStation
// point 3-5 of consistency
//bool check_line_track(unordered_map<int, Tram *> trams, unordered_map<string, Station*> stations) {
//  bool is_ok = true;
//  unordered_map<int, Tram*>::iterator it;
//  for (it = trams.begin(); it != trams.end() && is_ok; it++) {
//    Tram* tram = it->second;
//    int line = tram->getLine();
//    // for debug
//    // cout << "Line " << line << endl;
//    string startStation = tram->getStartStationName();
//    // for debug
//    // cout << "StartStation " << startStation << endl;
//    unordered_map<string, Station*>::iterator it1;
//    it1 = stations.find(startStation);
//    // for debug
//    // cout << "Ok " << (it1 != stations.end()) << endl;
//    if(it1 != stations.end()) {
//      Station* station = it1->second;
//      if(station->getTrack() != line)
//        is_ok = false; // if line != track, point 3 of consistency
//    }
//    else // if startStation of a tram is not in the subway, point 5 of consistency
//      is_ok = false;
//  }
//  return is_ok;
//}

SuccessEnum SubwaySimulationImporter::importSubway(const char *inputFileName, std::ostream& errStream, Subway& subway) {
  TiXmlDocument doc;
  SuccessEnum endResult = Success;

  if (!doc.LoadFile(inputFileName)) {
    errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc();
    return ImportAborted;
  }

  // These maps will contain objects parsed with the Parsing class
  vector<Station*> stationsArray;
  vector<Tram*> tramsArray;

  unordered_map<string, Station*> stations; // station name - station
  typedef pair<int, int> pair;
  map<pair, Tram*> trams;

  // Iterate through the file
  for (TiXmlElement *root = doc.FirstChildElement(); root != NULL; root = root->NextSiblingElement()) {
    // Root name must be either station or tram. Other values should be considered invalid.
    string rootName = root->Value();
    RootElementType rootElementType = determineRootElementType(rootName);

    switch (rootElementType) {
      case StationT: {
        // Create new Station object to hold the parsed data
        Station *station = parseStation(root, errStream);
        // This station doesn't have the correct data, so we'll skip to the next root and print an error message
        if (station == NULL) {
          errStream << "XML PARTIAL IMPORT: invalid station found" << endl;
          endResult = PartialImport;
        } else {
          // Check if there aren't stations already parsed with the same name to avoid duplicates
          // The count would be 1 if the element is indeed present in the map.
          if (stations.count(station->getName())) {
            // We found a duplicate. Exit early.
            errStream << "XML IMPORT ABORTED: found duplicate station with name " << station->getName() << endl;
            return ImportAborted;
          } else {
            // First time we're seeing a station with this name. Add this to our map.
            stations[station->getName()] = station;
            stationsArray.push_back(station);
          }
        }
        break;
      }
      case TramT: {
        // Create new Tram object to hold the parsed data
        Tram *tram = parseTram(root, errStream);
        if (tram == NULL) {
          errStream << "XML PARTIAL IMPORT: invalid tram found" << endl;
          endResult = PartialImport;
        } else {
          // Check if there aren't trams already parsed with the same line to avoid duplicates
          // The count would be 1 if the element is indeed present in the map.
          if (trams.count(make_pair(tram->getLine(), tram->getNumber()))) {
            // We found a duplicate. Exit early.
            errStream << "XML IMPORT ABORTED: found duplicate tram with line " << tram->getLine() << endl;
            return ImportAborted;
          } else {
            // First time we're seeing a tram with this line. Add this to our map.
            trams[make_pair(tram->getLine(), tram->getNumber())] = tram;
            tramsArray.push_back(tram);
          }
        }
        break;
      }
      case InvalidT: {
        // If the root element has an unrecognized name then skip to next root element
        endResult = PartialImport;
        errStream << "UNRECOGNIZED ELEMENT with name " << rootName << ". Expected <previous> ... </previous>." << endl;
        break;
      }
    }
  }

  if (stationsArray.size() == 0 && trams.size() == 0) {
    errStream << "XML IMPORT ABORTED: found empty file";
    return ImportAborted;
  }

  // Consistency

  // Check points 2 - 4 of consistency
//  bool prev_next_track_tram = check_prev_next_track_tram(stations, trams);
//  if (!prev_next_track_tram) {
//    errStream << "XML IMPORT ABORTED: Some stations don't have a next and/or right station or there's a missing tram" << endl;
//    return ImportAborted;
//  }

  // Check points 3 - 5 of consistency
//  bool line_track = check_line_track(trams, stations);
//  if (!line_track) {
//    errStream << "XML IMPORT ABORTED: the lines don't correspond to the tracks" << endl;
//    return ImportAborted;
//  }

  // Link objects
  // Transform station names into Station pointers
  for (auto &station: stationsArray) {
    for (auto &track: station->getTracksArray()) {
      string nextStationName = track->getNextStr();
      string previousStationName = track->getPreviousStr();

      Station *nextStation = stations[nextStationName];
      Station *previousStation = stations[previousStationName];

      track->setNext(nextStation);
      track->setPrevious(previousStation);
    }
  }

  // Transform station names into Station pointers
  for (auto &tram: tramsArray) {
    string startStationName = tram->getStartStationName();
    Station *startStation = stations[startStationName];
    tram->setStartStation(startStation);
    tram->setCurrentStation(startStation);
  }

  subway.importData(stationsArray, tramsArray);

  doc.Clear();
  return endResult;
}

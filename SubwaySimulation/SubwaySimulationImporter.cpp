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

int maxStationChildrenCount = 4; // name, track1, track2, type
int maxTramChildrenCount = 4; // line, vehicle, type, startStation
int maxTrackChildrenCount = 3; // track, next, previous

enum RootElementType {StationT, TramT, TrackT, InvalidT};

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
  } else if (rootName == "TRACK") {
    return TrackT;
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
  if (childrenCount != maxTramChildrenCount) {
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

  // The attributes of a station are name, previous, next, track
  TiXmlNode *elem_name, *elem_type;

  elem_name = root->FirstChild("name");
  elem_type = root->FirstChild("type");

  if (elem_name == NULL || elem_type == NULL) {
    return NULL;
  }

  int childrenCount = 0;

  for (TiXmlElement *node = root->FirstChildElement(); node; node = node->NextSiblingElement()) {
    childrenCount++;

    // elem_value can be name, type, TRACK
    string elem_value = node->Value();

    // Parse track
    if (elem_value == "TRACK") {
      Track *track = parseTrack(node, errStream);
      if (track != NULL) {

      } else {
        // Invalid track, doesn't count towards children count
        childrenCount--;
      }
    }
  }

  if (childrenCount != maxStationChildrenCount) {
    return NULL;
  }

  string name = fetch_text(elem_name, errStream);
  string type = fetch_text(elem_type, errStream);

  // Check these are made up of letters ONLY
  if (!ValidStringAttribute(name)) {
    return NULL;
  }

  StationType typeStation;

  // check if the type is correct
  if (type == "station") {
    typeStation = TypeStation;
  } else if (type == "stop") {
    typeStation = TypeStop;
  } else {
    // Invalid station type means invalid station
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

  // Check that the number of children is 4
  int childrenCount = 0;
  for (const TiXmlNode* node = root->FirstChild(); node; node = node->NextSibling()) {
    childrenCount++;
  }

  if (childrenCount != maxTramChildrenCount) {
    return NULL;
  }

  // The attributes of a tram are line, capacity, speed and start station
  TiXmlNode *elem_startStation, *elem_line, *elem_type, *elem_vehicle;

  elem_line = root->FirstChild("line");
  elem_type = root->FirstChild("type");
  elem_startStation = root->FirstChild("startStation");
  elem_vehicle = root->FirstChild("vehicle");

  if (elem_startStation == NULL || elem_type == NULL || elem_line == NULL || elem_vehicle == NULL) {
    return NULL;
  }

  int line;
  int vehicle;
  TramType type;

  string startStation = fetch_text(elem_startStation, errStream);
  string typeStr = fetch_text(elem_type, errStream);
  string lineStr = fetch_text(elem_line, errStream);
  string vehicleStr = fetch_text(elem_vehicle, errStream);

  if (!ValidStringAttribute(startStation)) {
    return NULL;
  }

  if (typeStr == "Albatross") {
    type = Albatross;
  } else if (typeStr == "PCC") {
    type = PCC;
  } else {
    // Invalid tram type means invalid tram
    return NULL;
  }

  if (IsStringNumber(lineStr)) {
    line = stoi(lineStr);
  } else {
    return NULL;
  }

  if (IsStringNumber(vehicleStr)) {
    vehicle = stoi(vehicleStr);
  } else {
    return NULL;
  }

  return new Tram(line, type, startStation, vehicle);
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
      case TrackT: {
        // Track tags not valid at root level
        // We fall back to the next case:
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
  std::vector<Station*>::iterator stationIterator;
  stationIterator = stationsArray.begin();
  for (stationIterator = stationsArray.begin(); stationIterator < stationsArray.end(); stationIterator++) {
//    Station *currentStation = *stationIterator;
//    string nextStationName = currentStation->getNextName();
//    string previousStationName = currentStation->getPreviousName();
//
//    Station *nextStation = stations[nextStationName];
//    Station *previousStation = stations[previousStationName];
//
//    currentStation->setNext(nextStation);
//    currentStation->setPrevious(previousStation);
  }

  // Transform station names into Station pointers
  std::vector<Tram*>::iterator tramIterator;
  tramIterator = tramsArray.begin();
  for (tramIterator = tramsArray.begin(); tramIterator < tramsArray.end(); tramIterator++) {
    Tram *currentTram = *tramIterator;
    string startStationName = currentTram->getStartStationName();
    Station *startStation = stations[startStationName];
    currentTram->setStartStation(startStation);
    currentTram->setCurrentStation(startStation);
  }

  subway.importData(stationsArray, tramsArray);

  doc.Clear();
  return endResult;
}

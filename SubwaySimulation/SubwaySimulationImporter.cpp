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
#include "tinyxml.h"

using namespace std;

// Auxiliary function for internal use only
const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
  if (pElement == NULL) return "";

  TiXmlNode *elemNode = pElement->FirstChild();
  if (elemNode == NULL) return "";
  TiXmlText* text = elemNode->ToText();
  if(text == NULL) return "";
  return text->Value();
}

// Check if this string is made up of letters ONLY
bool is_letters_only(string string) {
  for (unsigned int i = 0; i < string.size(); i++) {
    char c = string[i];
    if (!isalpha(c) || isdigit(c) || isspace(c)) {
      return false;
    }
  }
  return true;
}

// Check if a given string is a number
bool is_number(std::string string) {
    std::regex e ("^-?\\d+");
    return std::regex_match(string, e);
}

// Parse station given its root element
Station *parseStation(TiXmlElement *root, std::ostream& errStream) {
  // Edge case: if the station is empty return null
  if (root->NoChildren()) {
    return NULL;
  }

  // Create new Station object to hold the parsed data
  Station *station = new Station();

  // The attributes of a station are name, previous, next, track
  TiXmlNode *elem_name, *elem_previous, *elem_next, *elem_track;
  elem_name = root->FirstChild("name");
  elem_previous = root->FirstChild("previous");
  elem_next = root->FirstChild("next");
  elem_track = root->FirstChild("track");

  int childrenCount = 0;
  for (const TiXmlNode* node = root->FirstChild(); node; node = node->NextSibling()) {
    childrenCount++;
  }

  if (childrenCount != 4) {
    return NULL;
  }

  if (elem_name == NULL || elem_previous == NULL || elem_next == NULL) {
    // Invalid format, return
    return NULL;
  }

  // Check these are made up of letters ONLY
  string name = fetch_text(elem_name, errStream);
  string previous = fetch_text(elem_previous, errStream);
  string next = fetch_text(elem_next, errStream);

  if (!is_letters_only(name) || !is_letters_only(previous) || !is_letters_only(next)) {
    return NULL;
  }

  station->setName(name);
  station->setPrevious(previous);
  station->setNext(next);

  string trackStr = fetch_text(elem_track, errStream);
  // If the track is a number, then return station
  if (is_number(trackStr)) {
    station->setTrack(stoi(trackStr));
    return station;
  } else {
    // Otherwise skip
    return NULL;
  }
}

// Parse station given its root element
Tram *parseTram(TiXmlElement *root, std::ostream& errStream) {
  // Edge case: if the tram is empty return null
  if (root->NoChildren()) {
    return NULL;
  }

  // Create new Station object to hold the parsed data
  Tram *tram = new Tram();

  // Check that the number of children is 4
  int childrenCount = 0;
  for (const TiXmlNode* node = root->FirstChild(); node; node = node->NextSibling()) {
    childrenCount++;
  }

  if (childrenCount != 4) {
    return NULL;
  }

  // The attributes of a tram are line, capacity, speed and start station
  TiXmlNode *elem_startStation, *elem_line, *elem_capacity, *elem_speed;

  elem_line = root->FirstChild("line");
  elem_capacity = root->FirstChild("capacity");
  elem_speed = root->FirstChild("speed");
  elem_startStation = root->FirstChild("startStation");

  string capacityStr, lineStr, speedStr;

  if (elem_startStation == NULL) {
    return NULL;
  }

  string startStation = fetch_text(elem_startStation, errStream);

  if (!is_letters_only(startStation)) {
    return NULL;
  }

  tram->setStartStation(startStation);
  capacityStr = fetch_text(elem_capacity, errStream);
  lineStr = fetch_text(elem_line, errStream);
  speedStr = fetch_text(elem_speed, errStream);

  if (is_number(capacityStr)) {
    tram->setCapacity(stoi(capacityStr));
  } else {
    return NULL;
  }

  if (is_number(lineStr)) {
    tram->setLine(stoi(lineStr));
  } else {
    return NULL;
  }

  if (is_number(speedStr)) {
    tram->setSpeed(stoi(speedStr));
  } else {
    return NULL;
  }

  return tram;
}

// A type can be either Station, Tram, or Invalid
RootElementType determineRootElementType(string rootName) {
  if (rootName == "STATION") {
    return StationType;
  } else if (rootName == "TRAM") {
    return TramType;
  } else {
    return InvalidType;
  }
}

int find_track(unordered_map<string, Station*> stations, unordered_map<string, Station*>::iterator it) {
  // Check if element exists in map or not
  /*for debug
  Element with key 'hat' found
  cout << "Found" << std::endl;
  Access the Key from iterator
  string key = it->first;
  cout << "NEXT " << key << endl;*/
  // Access the next/previous station from iterator
  Station* station = it->second;
  // Access the track of next/previous station
  int track = station->getTrack();
  // print for debug
  //cout << "key = " << key << " track = " << track << std::endl;
  return track;
}

// Check if each station has a next and previous with same track and if each track has exactly one tram
// point 2 - 4 of consistency
bool check_prev_next_track_tram(unordered_map<string, Station*> stations, unordered_map<int, Tram *> trams){
  bool is_ok = true;
  unordered_map<string, Station*>::iterator it;
  for (it = stations.begin(); it != stations.end() && is_ok; it++) {
    Station *station = it->second;
    string next = station->getNext();
    string prev = station->getPrevious();
    int track = station->getTrack();

    // check if each track has exactly one tram: it counts how many trams have line == track
    // point 4 of consistency
    if(trams.count(track) != 1)
      is_ok = false;

    // for debug
    /*cout << "NAME " << station->getName() << endl;
    cout << "NEXT " << station->getNext() << endl;
    cout << "PREV " << station->getPrevious() << endl;
    cout << "TRACK " << station->getTrack() << endl;*/
    // iterator for next
    unordered_map<string, Station*>::iterator it1;
    // Find next station
    it1 = stations.find(next);
    // iterator for previous
    unordered_map<string, Station*>::iterator it2;
    // Find previous station
    it2 = stations.find(prev);
    // for debug
    /*unordered_map<string, Station*>::iterator it3;
    for (it3 = stations.begin(); it3 != stations.end(); ++it3)
        cout << it3->first << " = "
             << it3->second << '\n';*/
    // Check if element exists in map or not
    if(it1 != stations.end() && it2 != stations.end()){
      int next_track = find_track(stations, it1);
      int prev_track = find_track(stations, it2);
      if(track == next_track && next_track == prev_track)
        is_ok =  true;
      else
        is_ok = false;
    }
    else
      is_ok = false;
  }
  return is_ok;
}

// Check if each tram has its startStation in the subway and its line corresponds to track of its startStation
// point 3-5 of consistency
bool check_line_track(unordered_map<int, Tram *> trams, unordered_map<string, Station*> stations) {
  bool is_ok = true;
  unordered_map<int, Tram*>::iterator it;
  for (it = trams.begin(); it != trams.end() && is_ok; it++) {
    Tram* tram = it->second;
    int line = tram->getLine();
    // for debug
    // cout << "Line " << line << endl;
    string startStation = tram->getStartStation();
    // for debug
    // cout << "StartStation " << startStation << endl;
    unordered_map<string, Station*>::iterator it1;
    it1 = stations.find(startStation);
    // for debug
    // cout << "Ok " << (it1 != stations.end()) << endl;
    if(it1 != stations.end()) {
      Station* station = it1->second;
      if(station->getTrack() != line)
        is_ok = false; // if line != track, point 3 of consistency
    }
    else // if startStation of a tram is not in the subway, point 5 of consistency
      is_ok = false;
  }
  return is_ok;
}

void printParsedObjects(vector<Station*> stations, unordered_map<int, Tram*> trams) {
  for (auto & station : stations) {
    cout << "Station " << station->getName() << endl
         << "<- Station " << station->getPrevious() << endl
         << "-> Station " << station->getNext() << endl
         << "Track " << station->getTrack();
    // If there's a tram associated to the track, print capacity
    if (trams.count(station->getTrack())) {
      Tram *tram = trams[station->getTrack()];
      if (tram->getStartStation() == station->getName()) {
        cout << ": Tram with " << tram->getCapacity() << " seats";
      }
    }
    cout << endl << endl;
  }
}

SuccessEnum SubwaySimulationImporter::importSubway(
    const char *inputFileName, std::ostream& errStream, Subway& subway) {
  TiXmlDocument doc;
  SuccessEnum endResult = Success;

  if (!doc.LoadFile(inputFileName)) {
    errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc();
    return ImportAborted;
  }

  // These maps will contain objects parsed with the Parsing class
  vector<Station*> stationsArray;
  unordered_map<string, Station*> stations; // station name - station
  unordered_map<int, Tram*> trams; // tram startStation - tram

  // Iterate through the file
  for (TiXmlElement *root = doc.FirstChildElement(); root != NULL; root = root->NextSiblingElement()) {
    // Root name must be either station or tram. Other values should be considered invalid.
    string rootName = root->Value();
    RootElementType rootElementType = determineRootElementType(rootName);

    switch (rootElementType) {
      case StationType: {
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
      case TramType: {
        // Create new Tram object to hold the parsed data
        Tram *tram = parseTram(root, errStream);
        if (tram == NULL) {
          errStream << "XML PARTIAL IMPORT: invalid tram found" << endl;
          endResult = PartialImport;
        } else {
          // Check if there aren't trams already parsed with the same line to avoid duplicates
          // The count would be 1 if the element is indeed present in the map.
          if (trams.count(tram->getLine())) {
            // We found a duplicate. Exit early.
            errStream << "XML IMPORT ABORTED: found duplicate tram with line " << tram->getLine() << endl;
            return ImportAborted;
          } else {
            // First time we're seeing a tram with this line. Add this to our map.
            trams[tram->getLine()] = tram;
          }
        }
        break;
      }
      case InvalidType: {
        // If the root element has an unrecognized name then skip to next root element
        endResult = PartialImport;
        errStream << "UNRECOGNIZED ELEMENT with name " << rootName << ". Expected <previous> ... </previous>." << endl;
        break;
      }
    }
  }

  if (stationsArray.size() == 0 || trams.size() == 0) {
    errStream << "XML IMPORT ABORTED: found empty file";
    return ImportAborted;
  }

  // Consistency

  // Check points 2 - 4 of consistency
  bool prev_next_track_tram = check_prev_next_track_tram(stations, trams);
  if (!prev_next_track_tram) {
    errStream << "XML IMPORT ABORTED: Some stations don't have a next and/or right station" << endl;
    return ImportAborted;
  }

  // Check points 3 - 5 of consistency
  bool line_track = check_line_track(trams, stations);
  if (!line_track) {
    errStream << "XML IMPORT ABORTED: the lines don't correspond to the tracks" << endl;
    return ImportAborted;
  }

  printParsedObjects(stationsArray, trams);

  doc.Clear();
  return endResult;
}

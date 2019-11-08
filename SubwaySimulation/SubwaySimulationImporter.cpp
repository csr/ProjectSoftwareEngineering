//============================================================================
// Name        : SubwaySimulationImporter.cpp
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#include "SubwaySimulationImporter.h"
#include <map>
#include <iostream>
#include <locale>
#include "tinyxml.h"
using namespace std;

//Auxiliary function for internal use only

const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
  if (pElement == NULL) return "";

  TiXmlNode *elemNode = pElement->FirstChild();
  if (elemNode == NULL) return "";
  TiXmlText* text = elemNode->ToText();
  if(text == NULL) return "";
  return text->Value();
}

// Check if this string is made up of letters ONLY
bool is_letters_only(string s) {
  for (char const &c: s) {
    if (!isalpha(c) || isdigit(c) || isspace(c)) {
      return false;
    }
  }
  return true;
}

// Check if a given string is a number
bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

// Parse station given its root element
Station *parseStation(TiXmlElement *root, std::ostream& errStream) {
  // Create new Station object to hold the parsed data
  Station *station = new Station();

  // The attributes of a station are name, previous, next, track
  TiXmlNode *elem_name, *elem_previous, *elem_next, *elem_track;
  elem_name = root->FirstChild("name");
  elem_previous = root->FirstChild("previous");
  elem_next = root->FirstChild("next");
  elem_track = root->FirstChild("track");

  if (elem_name == NULL || elem_previous == NULL || elem_next == NULL) {
    // Invalid format, return
    return NULL;
  }

  // Check these are made up of letters ONLY
  string name = fetch_text(elem_name, errStream);
  string previous = fetch_text(elem_previous, errStream);
  string next = fetch_text(elem_next, errStream);

  if (!is_letters_only(name)) {
    return NULL;
  }
  if (!is_letters_only(previous)) {
    return NULL;
  }
  if (!is_letters_only(next)) {
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
  // Create new Station object to hold the parsed data
  Tram *tram = new Tram();

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

  tram->setStartStation(fetch_text(elem_startStation, errStream));
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

SuccessEnum SubwaySimulationImporter::importSubway(
    const char *inputFileName, std::ostream& errStream, Subway& subway) {
  TiXmlDocument doc;
  SuccessEnum endResult = Success;

  if (!doc.LoadFile(inputFileName)) {
    cerr << doc.ErrorDesc() << endl;
    return FailedWithInvalidFileName;
  }

  // These maps will contain objects parsed with the Parsing class
  map<string, Station*> stations;
  map<int, Tram*> trams;

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
          errStream << "Error: Invalid station found." << endl;
          endResult = SuccessWithInvalidData;
        } else {
          // Add this to our model
          cout << "Parsed station with name: " << station->getName() << endl;
          stations[station->getName()] = station;
        }
        break;
      }
      case TramType: {
        // Create new Tram object to hold the parsed data
        Tram *tram = parseTram(root, errStream);
        if (tram == NULL) {
          errStream << "Error: Invalid tram found." << endl;
          endResult = SuccessWithInvalidData;
        } else {
          // Add this to our model
          trams[tram->getLine()] = tram;
        }
        break;
      }
      case InvalidType: {
        // If the root element has an unrecognized name then skip to next root element
        endResult = SuccessWithInvalidData;
        errStream << "UNRECOGNIZED ELEMENT with name " << rootName << ". Expected <previous> ... </previous>." << endl;
        break;
      }
    }
  }

  doc.Clear();
  return endResult;
}

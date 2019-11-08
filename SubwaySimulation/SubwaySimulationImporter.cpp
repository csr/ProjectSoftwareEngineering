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

// check if a string is composed by only digits -> it gives true if only digit / ""
bool check_digit(string s, int i, bool is_ok){
  while(is_ok and i < s.length()){
    if (!(isdigit(s.at(i)))){
      is_ok = false;
    }
    i++;
  }
  return is_ok;
}

// check if a string is composed by only letters
bool check_letter(string s, int i, bool is_ok) {
  while (is_ok and i < s.length()) {
    if (!(isalpha(s.at(i)))) {
      is_ok = false;
    }
    i++;
  }
  return is_ok;
}

// set the attribute of the station
void set_values_station(string elemName, Station* station, string attributeValue) {
  if(elemName == "track")
    station->setTrack(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
  else if(elemName == "name")
    station->setName(attributeValue);
  else if(elemName == "previous")
    station->setPrevious(attributeValue); //name perche prima lo salviamo solo come stringa,
    //solo quando si controlla la consistenza si fara cambio con un puntatore
  else if(elemName == "next") //name perche prima lo salviamo solo come stringa,
    //solo quando si controlla la consistenza si fara cambio con un puntatore
    station->setNext(attributeValue);
}

// check that the attribute is right for grammatic and if it is, it sets the value of the attribute to the station
bool check_digits_letters_station(string elemName, string attributeValue, Station* station){
  int i = 0;
  bool is_ok = true;
  if(elemName == "name"){
    if(attributeValue.length() > 0) {
      is_ok = check_letter(attributeValue, i, is_ok); // it is false if the string contains not letters or it is ""else
    }
    else
      is_ok = false; // is attributeValue == "" -> error here in "name", it can not be ""
  }
  else if(elemName == "previous" || elemName == "next"){
    if(attributeValue.length() > 0) // check if there are only letters only if the string is not "", it can be "" here
      // in teoria non e' necessario questo if , perche' check_letter da' true se controlla su stringa  ""
      is_ok = check_letter(attributeValue, i, is_ok);
  }
  else if(elemName == "track"){
    is_ok = check_digit(attributeValue, i, is_ok);
  }
  if(is_ok == false){
    cout << "DATA NOT CONSISTENT FOR STATION" << endl;
  }
  else {// if is_ok
    set_values_station(elemName, station, attributeValue);
  }
  return is_ok;
}

// set the attribute of the tram
void set_values_tram(string elemName, Tram* tram, string attributeValue){
  if(elemName == "line")
    tram->setLine(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
  else if(elemName == "capacity")
    tram->setCapacity(std::stoi(attributeValue));
  else if(elemName == "speed")
    tram->setSpeed(std::stoi(attributeValue));
  else if(elemName == "startStation")
    tram->setStartStation(attributeValue);
}

// check that the attribute is right for the grammar and if it is, it sets the value of the attribute to the tram
bool check_digits_letters_tram(string elemName, string attributeValue, Tram* tram) {
  int i = 0;
  bool is_ok = true;
  if (elemName == "line" || elemName == "speed" || elemName == "capacity")
    is_ok = check_digit(attributeValue, i, is_ok);
  else if (elemName == "startStation")
    is_ok = check_letter(attributeValue, i, is_ok);
  if (is_ok == false){
    cout << "DATA NOT CONSISTENT FOR TRAM" << endl;
  }
  else {// if is_ok
    set_values_tram(elemName, tram, attributeValue);
  }
  return is_ok;
}

SuccessEnum SubwaySimulationImporter::importSubway(
    const char *inputFileName, std::ostream& errStream, Subway& subway) {
  TiXmlDocument doc;
  SuccessEnum endResult = Success;

  cout << "Trying to load file with name: " << inputFileName << "\n";

  if (!doc.LoadFile(inputFileName)) {
    cerr << doc.ErrorDesc() << endl;
    return InvalidFileName;
  }

  return endResult;

  // These maps will contain objects parsed with the Parsing class
//  map<string, Station*> stations;
//  map<string, Tram*> trams;
//
//  for (TiXmlElement *root = doc.FirstChildElement(); root != NULL; root = root->NextSiblingElement()) {
//    string rootName = root->Value();
//    if (rootName != "STATION" && rootName != "TRAM") {
//      cout << "UNRECOGNIZED ELEMENT: Expected <STATION> ... </STATION> or <TRAM> ... </TRAM> and got <"
//           << rootName << "> ... </" << rootName << ">." << endl;
//    } else if (rootName == "STATION") { // AGGIUNGERE LA STAZIONE CREATA ALLA MAP
//      cout << "Root station: " << rootName << endl;
//      Station* station = new Station(); // putatore a ogg di tipo station che sta in heap
//      // children of root
//      TiXmlNode *elem_name, *elem_previous, *elem_next, *elem_track;
//      // children of root -> string
//      string name_string, previous_string, next_string, track_string;
//      // attribute of children of root -> string
//      string name, previous, next, track; // they contain the value of the attribute as String
//      // check if there are name, previous, next, track
//      elem_name = root->FirstChild("name");
//      // cout << "???? " << elem_name << endl;
//      elem_previous = root->FirstChild("previous");
//      elem_next = root->FirstChild("next");
//      elem_track = root->FirstChild("track");
//      if (elem_name == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <name> ... </name>." << endl;
//        endResult = InvalidData;
//        name = "";
//      } else {
//        name_string = elem_name->Value();
//        name = fetch_text(elem_name, errStream); // string del valore dell'attributo name
//        cout << "El name: " << name_string << endl;
//        cout << "Attr name: " << name << endl;
//        if (name != "") {
//          bool data_ok = check_digits_letters_station(name_string, name, station); // station e' un puntatore
//          //cout << "NAME " << station->getName() << endl;
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      if (elem_previous == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <previous> ... </previous>." << endl;
//        endResult = InvalidData;
//        previous = "";
//      } else {
//        previous_string = elem_previous->Value();
//        previous = fetch_text(elem_previous, errStream); // string del valore dell'attributo name
//        cout << "El previous: " << previous_string << endl;
//        cout << "Attr previous: " << previous << endl;
//        if (previous != ""){
//          bool data_ok = check_digits_letters_station(previous_string, previous, station);
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      if (elem_next == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <next> ... </next>." << endl;
//        endResult = InvalidData;
//        next = "";
//      } else {
//        next_string = elem_next->Value();
//        next = fetch_text(elem_next, errStream); // string del valore dell'attributo name
//        cout << "El next: " << next_string << endl;
//        cout << "Attr next: " << next << endl;
//        if (next != "") {
//          bool data_ok = check_digits_letters_station(next_string, next, station);
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      if (elem_track == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <track> ... </track>." << endl;
//        endResult = InvalidData;
//        track = "";
//      } else {
//        track_string = elem_track->Value();
//        track = fetch_text(elem_track, errStream); // string del valore dell'attributo name
//        cout << "El track: " << track_string << endl;
//        cout << "Attr track: " << track << endl;
//        if (track != "") {
//          bool data_ok = check_digits_letters_station(track_string, track, station);
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      cout << "ENDRESULT station " << endResult << endl;
//      if (endResult == 0){
//        stations[name] = station;
//
//        // for debugging
//        map<string, Station*>::iterator it;
//        std::cout <<"STATIONS:" << endl;
//        for ( it = stations.begin(); it != stations.end(); it++ )
//        {
//          std::cout << it->first  // string (key)
//                    << ':'
//                    << it->second->getName()   // string's value
//                    << "  "
//                    << it->second->getPrevious()
//                    << "  "
//                    << it->second->getNext()
//                    << "  "
//                    << it->second->getTrack()
//                    << std::endl ;
//        }
//      }
//    } else if (rootName == "TRAM") { // AGGIUNGERE IL TRAM CREATO ALLA MAP
//      Tram* tram = new Tram();
//      // children of root
//      TiXmlNode *elem_line, *elem_capacity, *elem_speed, *elem_startStation;
//      // children of root -> string
//      string line_string, capacity_string, speed_string, startStation_string;
//      // attribute of children of root -> string
//      string line, capacity, speed, startStation; // they contain the value of the attribute as String
//      // check if there are name, previous, next, track
//      elem_line = root->FirstChild("line");
//      elem_capacity = root->FirstChild("capacity");
//      elem_speed = root->FirstChild("speed");
//      elem_startStation = root->FirstChild("startStation");
//      if (elem_line == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <line> ... </line>." << endl;
//        endResult = InvalidData;
//        line = "";
//      } else {
//        line_string = elem_line->Value();
//        line = fetch_text(elem_line, errStream); // string del valore dell'attributo name
//        cout << "El line: " << line_string << endl;
//        cout << "Attr line: " << line << endl;
//        if (line != "") {
//          bool data_ok = check_digits_letters_tram(line_string, line, tram);
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      if (elem_capacity == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <capacity> ... </capacity>." << endl;
//        endResult = InvalidData;
//        capacity = "";
//      } else {
//        capacity_string = elem_capacity->Value();
//        capacity = fetch_text(elem_capacity, errStream); // string del valore dell'attributo name
//        cout << "El capacity: " << capacity_string << endl;
//        cout << "Attr capacity: " << capacity << endl;
//        if (capacity != "") {
//          bool data_ok = check_digits_letters_tram(capacity_string, capacity, tram);
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      if (elem_speed == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <speed> ... </speed>." << endl;
//        endResult = InvalidData;
//        speed = "";
//      } else {
//        speed_string = elem_speed->Value();
//        speed = fetch_text(elem_speed, errStream); // string del valore dell'attributo name
//        cout << "El speed: " << speed_string << endl;
//        cout << "Attr speed: " << speed << endl;
//        if (speed != "") {
//          bool data_ok = check_digits_letters_tram(speed_string, speed, tram);
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      if (elem_startStation == NULL) {
//        cout << "UNRECOGNIZED ELEMENT: Expected <startStation> ... </startStation>." << endl;
//        endResult = InvalidData;
//        startStation = "";
//      } else {
//        startStation_string = elem_startStation->Value();
//        startStation = fetch_text(elem_startStation, errStream); // string del valore dell'attributo name
//        cout << "El startStation: " << startStation_string << endl;
//        cout << "Attr startStation: " << startStation << endl;
//        if (startStation != "") {
//          bool data_ok = check_digits_letters_tram(startStation_string, startStation, tram);
//          if (data_ok == false) {
//            cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//            endResult = InvalidData;
//          }
//        }
//        else {
//          cout << "INVALID DATA FOR ATTRIBUTE" << endl;
//          endResult = InvalidData;
//        }
//      }
//      cout << "ENDRESULT tram " << endResult << endl;
//      if (endResult == 0){
//        trams[line] = tram;
//
//        // for debugging
//        map<string, Tram*>::iterator it;
//        std::cout <<"TRAM:" << endl;
//        for ( it = trams.begin(); it != trams.end(); it++ )
//        {
//          std::cout << it->first  // string (key)
//                    << ':'
//                    << it->second->getLine()   // string's value
//                    << "  "
//                    << it->second->getCapacity()
//                    << "  "
//                    << it->second->getSpeed()
//                    << "  "
//                    << it->second->getStartStation()
//                    << std::endl ;
//        }
//      }
//    }
//  }
//  cout << "result: " << endResult << endl;
//
//  doc.Clear();
//  return endResult;
}

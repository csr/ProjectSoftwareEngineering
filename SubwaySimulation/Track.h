//============================================================================
// Name        : Track.h
// Author      : Group A
// Version     :
// Copyright   : Group A
// Description : Subway simulation in C++
//============================================================================

#ifndef SUBWAYSIMULATION_TRACK_H
#define SUBWAYSIMULATION_TRACK_H

#include "Station.h"
#include <string>

using namespace std;

// Example Track:
//<TRACK>
//<track>12</track>
//<next>A</next>
//<previous>B</previous>
//</TRACK>

class Station;

class Track {
 public:
  Track(int track, string next, string previous);

  bool properlyInitialized();

  void setTrack(int track);

  void setNext(Station* next);

  void setPrevious(Station* previous);

  void setNextStr(string next);

  void setPreviousStr(string previous);

  int getTrack();

  Station* getNext();

  Station* getPrevious();

  string getNextStr();

  string getPreviousStr();

private:
   Track* _init;
   int _track;
   Station* _next;
   Station* _previous;
   string _nextStr;
   string _previousStr;
};

#endif //SUBWAYSIMULATION_TRACK_H

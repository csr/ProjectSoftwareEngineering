//============================================================================
// Name        : Track.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

#ifndef SUBWAYSIMULATION_TRACK_H
#define SUBWAYSIMULATION_TRACK_H

#include "Station.h"

// Example Track:
//<TRACK>
//<track>12</track>
//<next>A</next>
//<previous>B</previous>
//</TRACK>

class Station;

class Track {
 public:

/**
  Constructor for the Track class.
*/
  Track(int track, Station* next, Station* previous);

  bool properlyInitialized();

  void setTrack(int track);

  void setNext(Station* next);

  void setPrevious(Station* previous);

  int getTrackNumber();

  Station* getNextStation();

  Station* getPreviousStation();

 private:
   Track* _init;
   int _track;
   Station* _next;
   Station* _previous;
};

#endif //SUBWAYSIMULATION_TRACK_H

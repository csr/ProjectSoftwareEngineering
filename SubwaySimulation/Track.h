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

class Track {
    public:
        Track(int track, Station* next, Station* previous);

        void setTrack(int track);


        void setNext(Station* next);

  /**
Setter for previous Station name.
@note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPreviousName");
@note ENSURE(ValidStringAttribute(getPreviousName()), "Station next name must be valid");
@note ENSURE(getPreviousName() == _previousName, "Station previous station name was not set correctly");
*/
  void setPrevious(Station* previous);
        int getTrack();
        Station* getNext();
        Station* getPrevious();
        bool properlyInitialized();
    private:
        Track& _init;
        int _track;
        Station* _next;
        Station* _previous;
};

#endif //SUBWAYSIMULATION_TRACK_H

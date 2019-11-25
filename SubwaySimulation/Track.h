//
// Created by bigboss98 on 24/11/19.
//

#ifndef SUBWAYSIMULATION_TRACK_H
#define SUBWAYSIMULATION_TRACK_H


#include "Station.h"

class Track {

    public:
        Track(int track, Station* next, Station* previous);
        void setTrack(int track);
        void setNext(Station* next);
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

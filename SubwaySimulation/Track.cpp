//
// Created by bigboss98 on 24/11/19.
//

#include "Track.h"
#include "DesignByContract.h"
#include "SubwaySimulationUtils.h"

Track::Track(int track, Station *next, Station *previous) {
    _init = this;
    setTrack(track);
    setNext(next);
    setPrevious(previous);
}

void Track::setNext(Station *next) {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
    _next = next;
}

void Track::setPrevious(Station *previous) {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
    _previous = previous;
}

void Track::setTrack(int track) {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
    _track = track;
    ENSURE(ValidIntegerAttribute(track), "Number of track is negative");
}

int Track::getTrack() {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
    return _track;
}

Station* Track::getNext() {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
    return _next;
}

Station* Track::getPrevious() {
    REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
    return _previous;
}

bool Track::properlyInitialized() {
    return _init == this;
}

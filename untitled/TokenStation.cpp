//
// Created by veror on 28/10/2019.
//

#include "TokenStation.h"

string TokenStation::getName() {
    return name;
}

string TokenStation::getNext() {
    return next;
}

string TokenStation::getPrevious() {
    return previous;
}

int TokenStation::getTrack() {
    return track;
}

void TokenStation::setName(string name) {
    TokenStation::name = name;
}

void TokenStation::setNext(string next) {
    TokenStation::next = next;
}

void TokenStation::setPrevious(string previous) {
    TokenStation::previous = previous;
}

void TokenStation::setTrack(int track) {
    TokenStation::track = track;
}

// PER IL MOMENTO COSTRUTTORE DI DEFAULT PERCHE' QUANDO COSTRUIAMO UN TOKEN NON SAPPIAMO I SUOI PARAMETRI
/*TokenStation::TokenStation(string name, string next, string previous, int track) :
name(name),
next(next),
previous(previous),
track(track) {}*/

//
// Created by bigboss98 on 29/12/19.
//

#include "Albatros.h"
#include "Tram.h"
#include "DesignByContract.h"

Albatros::Albatros(int line, string startStation, int number): Tram(line, Albatross, startStation, number) {

}

int Albatros::calculateDistance() {
    int distance = 7200 / getSpeed();
    distance++;
    ENSURE(distance >= 0, "Distance can not be negative");
    Station* elem = this->getCurrentStation()->getTrack(this->getLine())->getNext();
    while(elem->getType() == TypeStop){
        distance += 7200 / _speed  + 1;
        elem = elem->getTrack(this->getLine())->getNext();
    }
    return distance;
}

bool Albatros::trackFree() {
    int track = this->getLine();

    Station* elem = this->getCurrentStation()->getTrack(track)->getNext();
    while(elem->getType() == TypeStop){
        if(elem->getTrack(track)->isCurrentlyOccupied())
            return false;
        elem = elem->getTrack(track)->getNext();

    }
    if (elem == this->getCurrentStation())
        return true;
    return !elem->getTrack(track)->isCurrentlyOccupied();
}

Station* Albatros::getNextStation() {
    REQUIRE(this->properlyInitialized(), "Albatros wasn't initialized when calling getNextStation");

    Station* next = this->getCurrentStation()->getTrack(this->getLine())->getNext();
    while(next->getType() == TypeStop){
        next = next->getTrack(this->getLine())->getNext();
    }
    return next;
}

int getMaxCapacity(){
    REQUIRE(this->properlyInitialized(), "Albatros wasn't initialized when calling getMaxCapacity");
    return _capacity;
}

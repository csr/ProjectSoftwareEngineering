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
 
  /**
     *Constructs a Track class with track number, next station, previous station as string
     * @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     * @param track
     * @param next
     * @param previous
     * @returns an instance of Track
     */
  Track(int track, string next, string previous);

 /**
     *Constructs a Track class with track number, next station, previous station as pointers
     * @note ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     * @param track
     * @param next
     * @param previous
     * @returns an instance of Track
     */
  Track(int track, Station* next, Station* previous);

  bool properlyInitialized();

 /**
   * Setter for the number of the Track
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
   * @note ENSURE(ValidIntegerAttribute(number), "Number of track is negative");
   * @note ENSURE(number == getTrack(), "Number of track is negative");
   * @param track
   */
  void setTrack(int track);

 /**
   * Setter for the next Station as pointer
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
   * @note ENSURE(next == getNext(), "Next station wasn't set correctly");
   * @param next
   */
  void setNext(Station* next);

 /**
   * Setter for the previous Station as pointer
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling setPrevious");
   * @note ENSURE(previous == getPrevious(), "Previous station wasn't set correctly");
   * @param previous
   */
  void setPrevious(Station* previous);

 /**
   * Setter for next Station as string
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized");
   * @note ENSURE(nextStr == getNextStr(), "Next station wasn't set correctly");
   * @param next
   */
  void setNextStr(string next);

 /**
   * Setter for previous Station as string
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling setPreviousStr");
   * ENSURE(previousStr == getPreviousStr(), "Previous station wasn't set correctly");
   * @param previous
   */
  void setPreviousStr(string previous);

 /**
   * Getter for the number of the Track
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getTrack");
   * @return Number of Track
   */
  int getTrack();

 /**
   * Getter for the next Station as pointer
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getNextStr");
   * @return Next Station
   */
  Station* getNext();

 /**
   * Getter for the previous Station as pointer
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getPrevious");
   * @return Previous Station
   */
  Station* getPrevious();

  /**
   * Getter for the next Station as string
   * @note REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getNextStr");
   * @return Next Station
   */
  string getNextStr();

 /**
   * Getter for the previous Station as string
   * @note  REQUIRE(this->properlyInitialized(), "Track wasn't properly initialized when calling getPreviousStr");
   * @return Previous Station
   */
  string getPreviousStr();

 /**
   * Says if a Track is currently occupied by a particular Tram
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling isCurrentlyOccupied");
   * @return If the Track is occupied
   */
  bool isCurrentlyOccupied();

 /**
   * Setter for Track to say that it is occupied by a Tram
   * @note REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setOccupied");
   * @note ENSURE(isOccupied == isCurrentlyOccupied(), "Station occupied was not set correctly");
   * @param isOccupied
   */
  void setOccupied(bool isOccupied);

private:
   Track* _init;
   int _track;
   Station* _next;
   Station* _previous;
   string _nextStr;
   string _previousStr;
   bool _isOccupied;
};

#endif //SUBWAYSIMULATION_TRACK_H

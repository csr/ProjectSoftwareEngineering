//============================================================================
// Name        : Station.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================


#ifndef UNTITLED_STATION_H
#define UNTITLED_STATION_H
#include <string>
using namespace std;

class Station {
 public:
  /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
  Station(string name, string nextStation, string previousStation, int track);

  bool properlyInitialized();

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getName");
*/
  string getName();

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNext");
*/
  string getNext();

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getPrevious");
*/
  string getPrevious();

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getTrack");
*/
  int getTrack();

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setName");
*/
  void setName(string name);

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNext");
*/
  void setNext(string next);

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setPrevious");
*/
  void setPrevious(string previous);

  /**
\n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setTrack");
*/
  void setTrack(int track);

 private:
  Station * _initCheck; //!use pointer to myself to verify whether I am properly initialized

  string _name;
  string _next;
  string _previous;
  int _track;
};

#endif //UNTITLED_STATION_H
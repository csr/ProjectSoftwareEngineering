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
  string toString();

  // Getters
  const string &getName() const;
  const string &getNext() const;
  const string &getPrevious() const;
  int getTrack() const;

  // Setters
  void setName(const string &name);
  void setNext(const string &next);
  void setPrevious(const string &previous);
  void setTrack(int track);

 protected:
  string name;
  string next;
  string previous;
  int track;
};

#endif //UNTITLED_STATION_H
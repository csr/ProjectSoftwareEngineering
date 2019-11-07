//============================================================================
// Name        : Tram.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : This file holds the header for the Tram class.
//============================================================================

#ifndef UNTITLED_TRAM_H
#define UNTITLED_TRAM_H
#include <string>
using  namespace std;

class Tram {
 public:
  int getLine() const;

  int getCapacity() const;

  int getSpeed() const;

  const string &getStartStation() const;

  void setLine(int line);

  void setCapacity(int capacity);

  void setSpeed(int speed);

  void setStartStation(const string &startStation);

 private:
  int line;
  int capacity;
  int speed;
  string startStation;

};


#endif //UNTITLED_TRAM_H
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
#import "SimulationObject.h"

using  namespace std;

enum TramDirection {Forward, Backward};

class Tram: public SimulationObject {
 public:
  /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
  Tram(int line, int capacity, int speed, string startStation);

  bool properlyInitialized();

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLine");
*/
  int getLine();

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCapacity");
*/
  int getCapacity();

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
*/
  int getSpeed();

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getStartStation");
*/
  string getStartStation();

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
   */
  string getCurrentStation();

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
 */
  TramDirection getDirection();

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLine");
*/
  void setLine(int line);

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCapacity");
*/
  void setCapacity(int capacity);

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSpeed");
*/
  void setSpeed(int speed);

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setStartStation");
*/
  void setStartStation(string startStation);

  /**
   \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
   */
  void setCurrentStation(string station);

  /**
\n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling switchDirection");
*/
  void switchDirection();

 private:
  Tram * _initCheck; //!use pointer to myself to verify whether I am properly initialized

  int _line;
  int _capacity;
  int _speed;
  string _startStation;
  string _currentStation;
  TramDirection _direction;
};

#endif //UNTITLED_TRAM_H

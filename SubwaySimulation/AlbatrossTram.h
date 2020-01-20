//
// Created by Marco Natali, Veronica Orsanigo and Cesare De Cal.
//

#ifndef SUBWAYSIMULATION_ALBATROS_H
#define SUBWAYSIMULATION_ALBATROS_H
#include "Tram.h"

class AlbatrossTram : public Tram {
 public:
  /**
      Constructs an Albatross class, derived by Tram class.
      @param line Line of the Tram.
      @param startStation Start Station of the Tram.
      @param number Number of Vehicle of the Tram
      @returns An instance of Albatross
  */
  AlbatrossTram(int line, string startStation, int number);

  /**
      Getter for the maximum capacity of the Albatros Tram.
      @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getMaxCapacity");
      @returns Capacity of the Tram.
  */
  int getMaxCapacity() override;

  /**
      Getter for the speed of the Albatros Tram.
      @note REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSpeed");
      @returns Speed of the Tram.
  */
  int getSpeed() override;

 private:
  int _speed = 70;
  int _capacity = 72;

  int calculateDistance() override;
  bool trackFree() override;
  Station* getNextStation() override;
};


#endif //SUBWAYSIMULATION_ALBATROS_H
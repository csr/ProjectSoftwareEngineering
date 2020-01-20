//
// Created by Marco Natali, Veronica Orsanigo and Cesare De Cal
//

#ifndef SUBWAYSIMULATION_PCC_TRAM_H
#define SUBWAYSIMULATION_PCC_TRAM_H
#include "Tram.h"

class PCCTram : public Tram{
    public:
        PCCTram(int line, string startStation, int number);
        
        /**
            Getter for the maximum capacity of the PCC Tram.
            @note REQUIRE(this->properlyInitialized(), "PCC Tram wasn't initialized when calling getMaxCapacity");
            @returns Capacity of the Tram.
        */       
        int getMaxCapacity() override;

        /**
            Getter for the speed of the PCC Tram.
            @note REQUIRE(this->properlyInitialized(), "PCC Tram wasn't initialized when calling getSpeed");
            @returns Speed of the Tram.
        */
        int getSpeed() override;


    private:
        int _speed = 40;
        int _capacity = 16;

        int calculateDistance() override;
        bool trackFree() override;
        Station* getNextStation() override;
};


#endif //SUBWAYSIMULATION_PCC_H

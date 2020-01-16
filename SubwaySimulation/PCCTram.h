//
// Created by bigboss98 on 29/12/19.
//

#ifndef SUBWAYSIMULATION_PCC_TRAM_H
#define SUBWAYSIMULATION_PCC_TRAM_H
#include "Tram.h"

class PCCTram : public Tram{
    public:
        PCCTram(int line, string startStation, int number);
        int calculateDistance() override;
        Station* getNextStation() override;
        bool trackFree() override;
        int getMaxCapacity() override;
        int getSpeed() override;


    private:
        int _speed = 40;
        int _capacity = 16;
};


#endif //SUBWAYSIMULATION_PCC_H

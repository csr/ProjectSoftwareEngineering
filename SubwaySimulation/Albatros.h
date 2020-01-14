//
// Created by bigboss98 on 29/12/19.
//

#ifndef SUBWAYSIMULATION_ALBATROS_H
#define SUBWAYSIMULATION_ALBATROS_H
#include "Tram.h"

class Albatros : public Tram {
    public:
        Albatros(int line, string startStation, int number);
        int calculateDistance() override;
        Station* getNextStation() override;
        bool trackFree() override ;
        int getMaxCapacity() override;

    private:
        int _speed = 70;
        int _capacity = 72;
};


#endif //SUBWAYSIMULATION_ALBATROS_H

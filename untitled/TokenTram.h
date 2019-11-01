//
// Created by veror on 28/10/2019.
//

#ifndef UNTITLED_TOKENTRAM_H
#define UNTITLED_TOKENTRAM_H


class TokenTram {

public:
    int line;
    int capacity;
    int speed;
    string startStation;

    // per il momento lasciamo il costruttore di default perche' quando creiamo un token non si conoscono i suoi
    // attributi, ma bisogna aggiungerli passo passo -> riga sotto commentata
    // TokenTram(int line, int capacity, int speed, string startStation);

    void setLine(int line);

    void setCapacity(int capacity);

    void setSpeed(int speed);

    void setStartStation(string startStation);

    int getLine() const;

    int getCapacity() const;

    int getSpeed() const;

    string getStartStation();
};


#endif //UNTITLED_TOKENTRAM_H

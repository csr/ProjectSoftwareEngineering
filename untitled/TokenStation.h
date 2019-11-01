//
// Created by veror on 28/10/2019.
//

#ifndef UNTITLED_TOKENSTATION_H
#define UNTITLED_TOKENSTATION_H
using std::string;

class TokenStation {

public:
    string name;
    string next;
    string previous;
    int track;

    // PER IL MOMENTO COSTRUTTORE DI DEFAULT PERCHE' QUANDO COSTRUIAMO UN TOKEN NON SAPPIAMO I SUOI PARAMETRI
    //TokenStation(string name, const string &next, const string &previous, int track);

    void setName(string name);

    void setNext(string next);

    void setPrevious(string previous);

    void setTrack(int track);

    string getName();

    string getNext();

    string getPrevious();

    int getTrack();
};


#endif //UNTITLED_TOKENSTATION_H

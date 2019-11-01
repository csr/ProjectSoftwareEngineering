//
// Created by veror on 28/10/2019.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#pragma once // NECESSARIO ??
#include "TokenStation.h"
#include "TokenTram.h"
//#include <string>
//include cose di TiXML
#include <vector>
#include "tinyxml.h"
using std::string;

class parser {

public:

    //DA MODIFICARE CON I METODI CREATI IN PARSER.CPP
    int openFile(string fileName);
    int findRoot(TiXmlDocument doc);
    void findChild(TiXmlElement* root, string rootName);
    void findValues(TiXmlElement* elem);
    //

    void setStations(const std::vector<TokenStation> &stations);

    void setTrams(const std::vector<TokenTram> &trams);

    const TiXmlDocument &getDoc() const;

    const std::vector<TokenStation> getStations();

    const std::vector<TokenTram> getTrams();

private:

    TiXmlDocument doc;
    // 2 vectors to contain things from parsing -> NB: controllare cosa bisogna importare e dichiarazioni !!!!!!!!!!
    std::vector<TokenStation> stations;
    std::vector<TokenTram> trams;

};


#endif //UNTITLED_PARSER_H

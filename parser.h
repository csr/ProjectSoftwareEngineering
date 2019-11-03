//
// Created by veror on 28/10/2019.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#include "Station.h"
#include "Tram.h"
#include "tinyxml.h"
#include <map>
using namespace std;

class parser {

public:

    static string fetch_text(TiXmlNode *elem);
    static bool check_digit(string s, int i, bool is_ok);
    static bool check_letter(string s, int i, bool is_ok);
    static void set_values_station(string elemName, Station station, string attributeValue);
    static void check_digits_letters_station(string elemName, string attributeValue, Station station);
    static void set_values_tram(string elemName, Tram tram, string attributeValue);
    static void check_digits_letters_tram(string elemName, string attributeValue, Tram tram);
    int parsing();

private:

    // 2 maps to contain things from parsing
    map<string, Station*> stations;
    map<string, Tram*> trams;

};


#endif //UNTITLED_PARSER_H

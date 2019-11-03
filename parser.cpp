//
// Created by veror on 28/10/2019.
//

// !!!!!!!!!!!!!!!!!!!!!!!!
// SISTEMARE PER STATION E TRAM (CLASSI) ED ECCEZIONI ERRSTREA
// !!!!!!!!!!!!!!!!!!!!!!!!!

// !!!!!!!!!!!!!!!!!!!!!!
// GESTIRE DOC.CLOSE()
// !!!!!!!!!!!!!!!!!!!!!!

// NB QUANDO SI USA UN OGGETTO (DI TIPO PUNTATORE) PER CHIAMARE UN METODO SI USA ->
#include "parser.h"
//#include "Station.h" NON INCLUDERE PERCHE' E' GIA' INCLUSO NELL'HEADER
//#include "Tram.h"
//#include <string>
//include cose di TiXML
//#include <vector>
#include <map>
#include <iostream>
#include "tinyxml.h"
#define FILE "example.txt" // metterci il nome del file XML che gli si passera' per testare
using namespace std;


// CONTROLLARE GET SET COSTRUTTORE, MAGARI TOGLIERLI A TIXMLDOCUMENT

// from an element to its attribute as string
/*string parser::fetch_text(TiXmlNode *elem){
    TiXmlNode *e = elem->FirstChild();
    if (e == NULL)
        return "null1";
    TiXmlText* text = elem->ToText();
    if(text == NULL)
        return "null2";
    cout << "attr" << text->Value();
    return text->Value();
}*/

string parser::fetch_text(TiXmlNode *elem){
    TiXmlNode *e = elem->FirstChild();
    if (e == NULL)
        return "";
    string attribute = e->Value();
    if(attribute == "")
        return "";
    return attribute;
}

// check if a string is composed by only digits -> it gives true if only digit / ""
bool parser::check_digit(string s, int i, bool is_ok){
    while(is_ok and i < s.length()){
        if (!(isdigit(s.at(i)))){
            is_ok = false;
        }
        i++;
    }
    return is_ok;
}

// check if a string is composed by only letters
bool parser::check_letter(string s, int i, bool is_ok) {
    while (is_ok and i < s.length()) {
        if (!(isalpha(s.at(i)))) {
            is_ok = false;
        }
        i++;
    }
    return is_ok;
}

// set the attribute of the station
void parser::set_values_station(string elemName, Station* station, string attributeValue){
    if(elemName == "track")
        station->setTrack(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
    else if(elemName == "name")
        station->setName(attributeValue);
    else if(elemName == "previous")
        station->setPrevious(attributeValue); //name perche prima lo salviamo solo come stringa,
        //solo quando si controlla la consistenza si fara cambio con un puntatore
    else if(elemName == "next") //name perche prima lo salviamo solo come stringa,
        //solo quando si controlla la consistenza si fara cambio con un puntatore
        station->setNext(attributeValue);
}

// check that the attribute is right for grammatic and if it is, it sets the value of the attribute to the station
bool parser::check_digits_letters_station(string elemName, string attributeValue, Station* station){
    int i = 0;
    bool is_ok = true;
    if(elemName == "name"){
        if(attributeValue.length() > 0) {
            is_ok = check_letter(attributeValue, i, is_ok); // it is false if the string contains not letters or it is ""else
        }
        else
            is_ok = false; // is attributeValue == "" -> error here in "name", it can not be ""
    }
    else if(elemName == "previous" || elemName == "next"){
        if(attributeValue.length() > 0) // check if there are only letters only if the string is not "", it can be "" here
            // in teoria non e' necessario questo if , perche' check_letter da' true se controlla su stringa  ""
            is_ok = check_letter(attributeValue, i, is_ok);
    }
    else if(elemName == "track"){
        is_ok = check_digit(attributeValue, i, is_ok);
    }
    if(is_ok == false){
        cout << "DATA NOT CONSISTENT FOR STATION" << endl;
    }
    else {// if is_ok
        set_values_station(elemName, station, attributeValue);
    }
    return is_ok;
}

// set the attribute of the tram
void parser::set_values_tram(string elemName, Tram* tram, string attributeValue){
    if(elemName == "line")
        tram->setLine(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
    else if(elemName == "capacity")
        tram->setCapacity(std::stoi(attributeValue));
    else if(elemName == "speed")
        tram->setSpeed(std::stoi(attributeValue));
    else if(elemName == "startStation")
        tram->setStartStation(attributeValue);
}

// check that the attribute is right for grammatic and if it is, it sets the value of the attribute to the tram
bool parser::check_digits_letters_tram(string elemName, string attributeValue, Tram* tram){
    int i = 0;
    bool is_ok = true;
    if (elemName == "line" || elemName == "speed" || elemName == "capacity")
        is_ok = check_digit(attributeValue, i, is_ok);
    else if (elemName == "startStation")
        is_ok = check_letter(attributeValue, i, is_ok);
    if (is_ok == false){
        cout << "DATA NOT CONSISTENT FOR TRAM" << endl;
    }
    else {// if is_ok
        set_values_tram(elemName, tram, attributeValue);
    }
    return is_ok;
}






// ////////////////////////////////////////////
// CONTROLLARE SE PASSARE FILE COME ATTRIBUTO ALLA FZ PARSING

// USARE OGGETTO PARSER PER CHIAMARE METODI E ATTRIBUTI

int parser::parsing() {

    //parser* p = new parser(); UTILE SOLO SE SI DEVE USARE UN METODO NON STATIC DELLA CLASSE parser (DEFINITA IN parser.h)

    TiXmlDocument doc;
    int endResult = 0;

    if (!doc.LoadFile(FILE)) {
        cerr << doc.ErrorDesc() << endl;
        return 1;
    }

    for (TiXmlElement *root = doc.FirstChildElement(); root != NULL; root = root->NextSiblingElement()) {
        endResult = 0;
        string rootName = root->Value();
        if (rootName != "STATION" && rootName != "TRAM") {
            cout << "UNRECOGNIZED ELEMENT: Expected <STATION> ... </STATION> or <TRAM> ... </TRAM> and got <"
                      << rootName << "> ... </" << rootName << ">." << endl;
        } else if (rootName == "STATION") { // AGGIUNGERE LA STAZIONE CREATA ALLA MAP
            cout << "Root station: " << rootName << endl;
            Station* station = new Station(); // putatore a ogg di tipo station che sta in heap
            TiXmlNode *elem_name, *elem_previous, *elem_next, *elem_track;
            string name_string, previous_string, next_string, track_string;
            string name, previous, next, track; // they contain the value of the attribute as String
            // check if there are name, previous, next, track
            elem_name = root->FirstChild("name");
                                    // cout << "???? " << elem_name << endl;
            elem_previous = root->FirstChild("previous");
            elem_next = root->FirstChild("next");
            elem_track = root->FirstChild("track");
            // get the elements above as String
            name_string = elem_name->Value();
            previous_string = elem_previous->Value();
            next_string = elem_next->Value();
            track_string = elem_track->Value();

            if (elem_name == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <name> ... </name>." << endl;
                endResult = 1;
                name = "";
            } else {
                name = fetch_text(elem_name); // string del valore dell'attributo name
                cout << "El name: " << name_string << endl;
                cout << "Attr name: " << name << endl;
                if (name != "") {
                    bool data_ok = check_digits_letters_station(name_string, name, station); // station e' un puntatore
                    //cout << "NAME " << station->getName() << endl;
                    if (data_ok == false) {
                        cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                        endResult = 1;
                    }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            if (elem_previous == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <previous> ... </previous>." << endl;
                endResult = 1;
                previous = "";
            } else {
                previous = fetch_text(elem_previous); // string del valore dell'attributo name
                cout << "El previous: " << previous_string << endl;
                cout << "Attr previous: " << previous << endl;
                if (previous != ""){
                    bool data_ok = check_digits_letters_station(previous_string, previous, station);
                    if (data_ok == false) {
                        cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                        endResult = 1;
                    }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            if (elem_next == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <next> ... </next>." << endl;
                endResult = 1;
                next = "";
            } else {
                next = fetch_text(elem_next); // string del valore dell'attributo name
                cout << "El next: " << next_string << endl;
                cout << "Attr next: " << next << endl;
                if (next != "") {
                    bool data_ok = check_digits_letters_station(next_string, next, station);
                    if (data_ok == false) {
                        cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                        endResult = 1;
                    }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            if (elem_track == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <track> ... </track>." << endl;
                endResult = 1;
                track = "";
            } else {
                track = fetch_text(elem_track); // string del valore dell'attributo name
                cout << "El track: " << track_string << endl;
                cout << "Attr track: " << track << endl;
                if (track != "") {
                    bool data_ok = check_digits_letters_station(track_string, track, station);
                    if (data_ok == false) {
                        cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                        endResult = 1;
                    }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            cout << "ENDRESULT station " << endResult << endl;
            if (endResult == 0){
                stations[name] = station;

                // for debugging
                map<string, Station*>::iterator it;
                std::cout <<"STATIONS:" << endl;
                for ( it = stations.begin(); it != stations.end(); it++ )
                {
                    std::cout << it->first  // string (key)
                              << ':'
                              << it->second->getName()   // string's value
                              << "  "
                              << it->second->getPrevious()
                              << "  "
                              << it->second->getNext()
                              << "  "
                              << it->second->getTrack()
                              << std::endl ;
                }

            }
        } else if (rootName == "TRAM") { // AGGIUNGERE IL TRAM CREATO ALLA MAP
            Tram* tram = new Tram();
            TiXmlNode *elem_line, *elem_capacity, *elem_speed, *elem_startStation;
            string line_string, capacity_string, speed_string, startStation_string;
            string line, capacity, speed, startStation; // they contain the value of the attribute as String
            // check if there are name, previous, next, track
            elem_line = root->FirstChild("line");
            elem_capacity = root->FirstChild("capacity");
            elem_speed = root->FirstChild("speed");
            elem_startStation = root->FirstChild("startStation");
            // get the elements above as String
            line_string = elem_line->Value();
            capacity_string = elem_capacity->Value();
            speed_string = elem_speed->Value();
            startStation_string = elem_startStation->Value();

            if (elem_line == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <line> ... </line>." << endl;
                endResult = 1;
                line = "";
            } else {
                line = fetch_text(elem_line); // string del valore dell'attributo name
                cout << "El line: " << line_string << endl;
                cout << "Attr line: " << line << endl;
                if (line != "") {
                    bool data_ok = check_digits_letters_tram(line_string, line, tram);
                    if (data_ok == false) {
                       cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                       endResult = 1;
                   }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            if (elem_capacity == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <capacity> ... </capacity>." << endl;
                endResult = 1;
                capacity = "";
            } else {
                capacity = fetch_text(elem_capacity); // string del valore dell'attributo name
                cout << "El capacity: " << capacity_string << endl;
                cout << "Attr capacity: " << capacity << endl;
                if (capacity != "") {
                    bool data_ok = check_digits_letters_tram(capacity_string, capacity, tram);
                    if (data_ok == false) {
                        cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                        endResult = 1;
                    }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            if (elem_speed == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <speed> ... </speed>." << endl;
                endResult = 1;
                speed = "";
            } else {
                speed = fetch_text(elem_speed); // string del valore dell'attributo name
                cout << "El speed: " << speed_string << endl;
                cout << "Attr speed: " << speed << endl;
                if (speed != "") {
                    bool data_ok = check_digits_letters_tram(speed_string, speed, tram);
                    if (data_ok == false) {
                        cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                        endResult = 1;
                    }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            if (elem_startStation == NULL) {
                cout << "UNRECOGNIZED ELEMENT: Expected <startStation> ... </startStation>." << endl;
                endResult = 1;
                startStation = "";
            } else {
                startStation = fetch_text(elem_startStation); // string del valore dell'attributo name
                cout << "El startStation: " << startStation_string << endl;
                cout << "Attr startStation: " << startStation << endl;
                if (startStation != "") {
                    bool data_ok = check_digits_letters_tram(startStation_string, startStation, tram);
                    if (data_ok == false) {
                        cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                        endResult = 1;
                    }
                }
                else {
                    cout << "INVALID DATA FOR ATTRIBUTE" << endl;
                    endResult = 1;
                }
            }
            cout << "ENDRESULT tram " << endResult << endl;
            if (endResult == 0){
                trams[line] = tram;

                // for debugging
                map<string, Tram*>::iterator it;
                std::cout <<"TRAM:" << endl;
                for ( it = trams.begin(); it != trams.end(); it++ )
                {
                    std::cout << it->first  // string (key)
                              << ':'
                              << it->second->getLine()   // string's value
                              << "  "
                              << it->second->getCapacity()
                              << "  "
                              << it->second->getSpeed()
                              << "  "
                              << it->second->getStartStation()
                              << std::endl ;
                }
            }
        }
    }
    //doc.Close();
    cout << "result: " << endResult << endl;
    return endResult;
}

// PARTE VECCHIA NON DA GUARDARE !!

            /*int numChildren = 0; // to check that the el STATION has 4 children at the end
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value(); // find child (es: if root == station -> elem = next)
                //std::cout << elemName << std::endl;
                if (elemName == "name" || elemName == "previous" || elemName == "next" || elemName == "track") {
                    TiXmlNode *e = elem->FirstChild(); // recupera l'attributo (es: if elem == "next" -> e = NOMESTAZIONE)
                    if (e != NULL) {
                        TiXmlText *text = e->ToText(); // recupera l'eattributo come puntatore a string
                        string attributeValue = "";
                        //if (text == NULL)
                        //  continuous;
                        //string t = text->Value();
                        //std::cout << t << std::endl;
                        if (text != NULL){ // elem non ha attributi -> puo' essere solo next previous
                            attributeValue = text->Value();
                            // check if the value is correct for the type of attribute
                            if(attributeValue != "")
                                check_digits_letters_station(elemName, attributeValue);
                            else {
                                // error: attributeValue is string ""
                            }
                        }
                        else {
                            // error: text == NULL -> attribute does not exist
                        }
                    }
                    else {
                        // error: attribute == NULL
                    }
                }
                else {
                    //error !! element not ok -> != next previous, name track
                }
                numChildren++;
            }
            if (numChildren != 4) {
                //errore !! la stazione manca di qualche elemento
            } else {
                stations.pushback(station); // DA FARE ALLA FINE, SE SI RISPATTANO LE REGOOLE DELLA GRAMMATICA
            }
            return 0; // COSì SI FA ??

        } else if (rootName == "TRAM") {
            TokenTram tram = new TokenTram();
            int numChildren = 0; // to check that the el STATION has 4 children at the end
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value(); // find child (es: if root == station -> elem = next)
                //std::cout << elemName << std::endl;
                if (elemName == "line" || elemName == "capacity" || elemName == "speed" || elemName == "startStation") {
                    TiXmlNode *e = elem->FirstChild(); // recupera l'attributo (es: if elem == "next" -> e = NOMESTAZIONE)
                    if (e != NULL) {
                        TiXmlText *text = e->ToText(); // recupera l'eattributo come puntatore a string
                        string attributeValue = "";
                        //if (text == NULL)
                        //  continuous;
                        //string t = text->Value();
                        //std::cout << t << std::endl;
                        if (text != NULL) {// elem non ha attributi -> puo' essere solo next previous
                            attributeValue = text->Value();
                            // check if the value is correct for the type of attribute
                            check_digits_letters_tram(elemName, attributeValue);
                        } else {
                            //errore !! zero argomenti dove dovrebbe essercene -> NULL insieme a track / name
                        }
                    } else {
                        //exceptin: value not ok, sono NULL
                    }
                } else { //error !! element not ok -> != line capacity speed startStation
                }
                numChildren++;
            }
            if (numChildren != 4) {
                //errore !! la stazione manca di qualche elemento
            } else {
                tram.spushback(tram); // DA FARE ALLA FINE, SE SI RISPATTANO LE REGOOLE DELLA GRAMMATICA
            }
            return 0; // COSì SI FA ??
        }
    }
}*/



// USEFUL FUNCTION TO CONTROL IF SYSTEM IS CONSISTENT

// consistent ? point 1 - 2

/*
check_track_close_station(std::vector<Station> stations){
for(int i = 0; i < stations.length() - 1; i++){
for(int j = 1; j < stations.lengh(); j++){ // aggiorna in automatico la lunghezza ??
if (stations[i].getName() == stations[j].getName()){
if(stations[i].getNext() == stations[j].getNext() && stations[i].getPrevious() == stations[j].getPrevious() && stations[i].getTrack() == stations[j].getTrack())
stations.erase(stations.begin() + j); // if there are 2 stations that are the same (same attributes), we cancel one
else
// errore !! stazioni hanno uguale nome, ma attributi differenti
}
else if(stations[i].getNextName() == stations[j].getName()) // if the station has a next == another station name
stations[i].setNext(&stations[j]); //giusto il deferenziamento ??
else if(stations[i].getPreviousName() == stations[j].getName()) // if the station has a previous == another station name
stations[i].setPrevious(&stations[j]);
}
}
*/

/*
void parser::setStations(const map<string, &stations) {
    parser::stations = stations;
}

const map<string, &parser::getStations() const {
    return stations;
}

const map<string, &parser::getTrams() const {
    return trams;
}

void parser::setTrams(const map<string, &trams) {
    parser::trams = trams;
}*/


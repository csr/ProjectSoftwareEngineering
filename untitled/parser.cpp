//
// Created by veror on 28/10/2019.
//

#include "parser.h"
#include "TokenStation.h"
#include "TokenTram.h"
//#include <string>
//include cose di TiXML
#include <vector>
#include <iostream>
#include "tinyxml.h"
using std::string;

// CONTROLLARE GET SET COSTRUTTORE, MAGARI TOGLIERLI A TIXMLDOCUMENT
const TiXmlDocument &parser::getDoc() const {
    return doc;
}

std::vector<TokenStation> getStations() {
    return stations;
}

std::vector<TokenTram> getTrams() {
    return trams;
}

void parser::setStations(const std::vector<TokenStation> &stations) {
    parser::stations = stations;
}

void parser::setTrams(const std::vector<TokenTram> &trams) {
    parser::trams = trams;
}

int openFile(string fileName){
    if (! doc.LoadFile (fileName)) {
        std::cerr << doc.ErrorDesc () << std :: endl;
        return 1;
    }
}

// check if a string is composed by only digits
boolean check_digit(string s, int i, boolean is_ok){
    while(is_ok and i < s.length()){
        if (!(isdigit(s.at(i)))){
            is_ok = false;
        }
        i++;
    }
    return is_ok;
}

boolean check_letter(string s, int i, boolean is_ok) {
    while (is_ok and i < s.length()) {
        if (!(isalpha(s.at(i)))) {
            is_ok = false;
        }
        i++;
    }
    return is_ok;
}

void check_digits_letters_station(string elemName, string attributeValue){
    int i = 0;
    boolean is_ok = true;
    if(elemName == "name"){
        if(attributeValue.length() > 0)
            is_ok = check_letter(attributeValue, i, is_ok); // it is false if the string contains not letters or it is ""else
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
        //exceptin: value not ok
    }
    else {// if is_ok
        set_values_station(elemName, station, attributeValue);
    }
}

void set_values_station(string elemName, TokenStation station, string attributeValue){
    if(elemName == "track")
        station.setTrack(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
    else if(elemName == "name")
        station.setName(attributeValue);
    else if(elemName == "previous")
        station.setPrevious(attributeValue); //name perche prima lo salviamo solo come stringa,
        //solo quando si controlla la consistenza si fara cambio con un puntatore
    else if(elemName == "next") //name perche prima lo salviamo solo come stringa,
        //solo quando si controlla la consistenza si fara cambio con un puntatore
        station.setNext(attributeValue);
}
void check_digits_letters_tram(string ElemName, string attributeValue){
    int i = 0;
    boolean is_ok = true;
    if (elemName = "line" || elemName == "speed" || elemName == "capacity")
        is_ok = check_digit(attributeValue, i, is_ok);
    else if (elemName == "startStation")
        is_ok = check_letter(attributeValue, i, is_ok);
    if (is_ok == false){
        //exceptin: value not ok
    }
    else {// if is_ok
        set_values_tram(elemName, tram, attributeValue);
    }
}

void set_values_tram(string elemName, TokenTram tram, string attributeValue){
    if(elemName == "line")
        tram.setLine(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
    else if(elemName == "capacity")
        tram.setCapacity(std::stoi(attributeValue));
    else if(elemName == "speed")
        tram.setSpeed(std::stoi(attributeValue));
    else if(elemName == "startStation")
        tram.setStartStation(attributeValue);
}

// find root, it must be "STATION" or "TRAM"
int findRoot(TiXmlDocument doc) {
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    } else {
        string rootName = root->Value();
        // std::cout << rootName << std::endl;
        // find element (attribute) of a root, they must be [name, previous, next, track (STATION)] / [line, capacity, startStation, speed (TRAM)]
        //void findChild(TiXmlElement* root, string rootName, ){
        if (rootName == "STATION") {
            TokenStation station = new TokenStation();
            int numChildren = 0; // to check that the el STATION has 4 children at the end
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
                        if (text != NULL) // elem non ha attributi -> puo' essere solo next previous
                            attributeValue = text->Value();
                        if (text != NULL || elemName == "previous" ||
                            elemName == "next") { // check that only previous or next can be null
                            // check if the value is correct for the type of attribute
                            check_digits_letters_station(elemName, attributeValue);
                        } else {
                            //errore !! zero argomenti dove dovrebbe essercene -> NULL insieme a track / name
                        }
                    } else if (elemName == "previous" ||
                               elemName == "next") { // check that only previous or next can be null
                        // check if the value is correct for the type of attribute
                        int i = 0;
                        boolean is_ok = true;
                        is_ok = check_letter(attributeValue, i, is_ok); // dovrebbe controllare che contenga solo lettere / sia "" ,
                        // in questo caso è restituito true, guarda codice di check_letter
                        if (is_ok == false) {
                            //exceptin: value not ok
                        } else {// if is_ok
                            set_values_station(elemName);
                        }
                    }
                } else { //error !! element not ok -> != next previous, name track
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
}



// USEFUL FUNCTION TO CONTROL IF SYSTEM IS CONSISTENT

// consistent ? point 1 - 2

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

/*
// find value of attribute, they must be [string (name, previous, next, startStation)] / [integer (track, line, capacity, speed)]
void findValues(TiXmlElement* elem, string elemName){
	for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
            TiXmlText *text = e->ToText();
            //if (text == NULL)
            //  continuous;
            string t = text->Value();
            //std::cout << t << std::endl;

			// check if the value is correct for the type of attribute
			int i = 0;
			boolean is_ok = true;
			if(elemName == "name" || elemName == "previous" || elemName == "next" || elemName == "startStation"){
				while(is_ok and i < t.length()){
					if (!((t.at(i) >= "a" && t.at(i) <= "z") || (t.at(i) >= "A" && t.at(i) <= "Z"))){
						is_letter = false;
					}
					i++;
				}
			}
			else if(elemName == "track" || elemName == "line" || elemName == "capacity" || elemName == "speed"){
				while(is_ok and i < t.length()){
					if (!(t.at(i) >= "0" && t.at(i) <= "9")){
						is_boolean = false;
					}
					i++;
				}
			}
			if(is_ok == false){
				//exceptin: value not ok
			}
			*/

void if_root(){

}


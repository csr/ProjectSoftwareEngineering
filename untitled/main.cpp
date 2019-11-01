#include <iostream>
#include "tinyxml.h"
#include "parser.h"
using std::string;

//#include <fstream>

// C'E' UN PROBLEMA DI PARENTESI QUI, PERCHE' DAL FILE DI ESEMPIO NON SI CAPISCE, PERO' I METODI SONO QUESTI

int openFile(string fileName) {
    if (! doc.LoadFile (fileName)) {
        std :: cerr << doc.ErrorDesc () << std :: endl;
        return 1;
    }
}

// find root, it must be "STATION" or "TRAM"
int findRoot(TiXmlDocument doc) {
    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }
    else {
        string rootName = root-> Value();
        // std::cout << rootName << std::endl;
        // find element (attribute) of a root, they must be [name, previous, next, track (STATION)] / [line, capacity, startStation, speed (TRAM)]
        //void findChild(TiXmlElement* root, string rootName, ){
        if (rootName == "STATION"){
            Station station = new Station();
            stations.pushback(station);
            int numChildren = 0;
            for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                std::string elemName = elem->Value(); // find child
                //std::cout << elemName << std::endl;
                if(elemName == "name" || elemName == "previous" || elemName == "next" || elemName == "track"){
                    int numAttributes = 0;
                    for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) { // prende lori attributi di child, però bisogna controllare che sia solo uno
                        TiXmlText *text = e->ToText();
                        string attributeValue = "";
                        //if (text == NULL)
                        //  continuous;
                        //string t = text->Value();
                        //std::cout << t << std::endl;
                        if (text != NULL){
                            attributeValue = text->Value();
                            numAttributes++;
                        }
                        if(numAttributes > 1){
                            //errore!! ci sono troppi attributi (es: due nomi di stazione, due track
                        }
                        else if((numAttributes == 0 && (elemName == "previous" or elemName == "next")) || numAttributes == 1){ // check that only previous or next can be null
                            // check if the value is correct for the type of attribute
                            int i = 0;
                            boolean is_ok = true;
                            if(elemName == "name" || elemName == "previous" || elemName == "next"){
                                while(is_ok and i < attributeValue.length()){
                                    if (!((attributeValue.at(i) >= "a" && attributeValue.at(i) <= "z") || (attributeValue.at(i) >= "A" && attributeValue.at(i) <= "Z"))){
                                        is_letter = false;
                                    }
                                    i++;
                                }
                            }
                            else if(elemName == "track"){
                                while(is_ok and i < attributeValue.length()){
                                    if (!(attributeValue.at(i) >= "0" && attributeValue.at(i) <= "9")){
                                        is_boolean = false;
                                    }
                                    i++;
                                }
                            }
                            if(is_ok == false){
                                //exceptin: value not ok
                            }
                            else{ // if is_ok
                                if(elemName == "track")
                                    station.setTrack(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
                                else if(elemName == "name")
                                    station.setName(attributeValue);
                                else if(elemName == "previous")
                                    station.setNamePrevious(attributeValue); //name perche prima lo salviamo solo come stringa,
                                    //solo quando si controlla la consistenza si fara cambio con un puntatore
                                else if(elemName == "next") //name perche prima lo salviamo solo come stringa,
                                    //solo quando si controlla la consistenza si fara cambio con un puntatore
                                    station.setNameNext(attributeValue);
                            }
                        }
                        else{
                            //errore !! zero argomenti dove dovrebbe essercene
                        }
                    }
                }
                numChildren++;
            }
            if(numChildren != 4)
                //errore !! la stazione manca di qualche elemento
                    else
            return 0; // COSì SI FA ??
        }
        else if (rootName == "TRAM"){
            Tram tram = new Tram();
            trams.pushback(tram);
            int numChildren = 0;
            for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                std::string elemName = elem->Value(); // find child
                //std::cout << elemName << std::endl;
                if(elemName == "line" || elemName == "capacity" || elemName == "speed" || elemName == "startStation"){
                    int numAttributes = 0;
                    for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) { // prende lori attributi di child, però bisogna controllare che sia solo uno
                        TiXmlText *text = e->ToText();
                        string attributeValue = "";
                        //if (text == NULL)
                        //  continuous;
                        //string t = text->Value();
                        //std::cout << t << std::endl;
                        if (text != NULL){
                            attributeValue = text->Value();
                            numAttributes++;
                        }
                        if(numAttributes != 1){
                            //errore!! ci sono troppi attributi (es: due nomi di stazione, due track
                        }
                        else { // if number of attributes is 1, here, in tram, there can be only defined attributes, I THINK
                            // check if the value is correct for the type of attribute
                            int i = 0;
                            boolean is_ok = true;
                            if(elemName == "startStation"){
                                while(is_ok and i < attributeValue.length()){
                                    if (!((attributeValue.at(i) >= "a" && attributeValue.at(i) <= "z") || (attributeValue.at(i) >= "A" && attributeValue.at(i) <= "Z"))){
                                        is_letter = false;
                                    }
                                    i++;
                                }
                            }
                            else if(elemName == "line" || elemName == "capacity" || elemName == "speed"){
                                while(is_ok and i < attributeValue.length()){
                                    if (!(attributeValue.at(i) >= "0" && attributeValue.at(i) <= "9")){
                                        is_boolean = false;
                                    }
                                    i++;
                                }
                            }
                            if(is_ok == false){
                                //exceptin: value not ok
                            }
                            else{ // if is_ok
                                if(elemName == "line")
                                    tram.setLine(std::stoi(attributeValue)); //bisogna aggiungere i set a classi Station e Tram
                                    // stoi used to cast from string to int
                                else if(elemName == "capacity")
                                    tram.setCapacity(std::stoi(attributeValue));
                                else if(elemName == "speed")
                                    tram.setSpeed(std::stoi(attributeValue));
                                else if(elemName == "startStation")
                                    tram.setNameStartStation(attributeValue); //name perche prima lo salviamo solo come stringa,
                                //solo quando si controlla la consistenza si fara cambio con un puntatore
                            }
                        }
                        else{
                            //errore !! zero argomenti dove dovrebbe essercene
                        }
                    }
                }
                numChildren++;
            }
            if(numChildren != 4)
                //errore !! la stazione manca di qualche elemento
                    else
            return 0; // COSì SI FA ??
        }
    }
    else {
        //exception invalid data/unrecognized element
        //return 2; ??
        //comme si fa poi a gestirlo nel ciclo
    }

}



// USEFUL FUNCTION TO CONTROL IF SYSTEM IS CONSISTENT

// consistent ? point 1 - 2

check_track_close_station(std::vector<Station> stations){
for(int i = 0; i < stations.length() - 1; i++){
for(int j = 1; j < stations.lengh(); j++) { // aggiorna in automatico la lunghezza ??
if (stations[i].getName() == stations[j].getName()) {
if (stations[i].getNext() == stations[j].getNext() &&
stations[i].getPrevious() == stations[j].getPrevious() &&
stations[i].getTrack() == stations[j].getTrack())
stations.erase(stations.begin() +
j); // if there are 2 stations that are the same (same attributes), we cancel one
else
// errore !! stazioni hanno uguale nome, ma attributi differenti
} else if (stations[i].getNextName() ==
stations[j].getName()) // if the station has a next == another station name
stations[i].setNext(&stations[j]); //giusto il deferenziamento ??
else if (stations[i].getPreviousName() ==
stations[j].getName()) // if the station has a previous == another station name
stations[i].setPrevious(&stations[j]);
}

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
    return 0;
}
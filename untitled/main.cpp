#include <iostream>
#include "tinyxml.h"

using std::string;

int main() {
    std::cout << "Hello, World!" << std::endl;

    TiXmlDocument doc;
    if (! doc.LoadFile ("example.xml")) {
        std :: cerr << doc.ErrorDesc () << std :: endl;
        return 1;
    } else {
        std::cout << "Ok, file found!" << std::endl;
    }


    TiXmlElement * root = doc.FirstChildElement (); if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        std::cout << elemName << std::endl;
    }
    return 0;
}


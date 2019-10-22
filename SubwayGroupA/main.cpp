#include <iostream>
#include "TinyXML/tinyxml.h"

using std::string;

void parseXMLFile() {
  TiXmlDocument doc;
  if (! doc.LoadFile ("example.xml")) {
    std :: cerr << doc.ErrorDesc () << std :: endl;
  } else {
    std::cout << "Ok, file found!" << std::endl;
  }

  TiXmlElement * root = doc.FirstChildElement (); if (root == NULL) {
    std::cerr << "Failed to load file: No root element." << std::endl;
    doc.Clear();
  }

  for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
    string elemName = elem->Value();
    std::cout << elemName << std::endl;
  }
}

int main() {
    parseXMLFile();
    return 0;
}
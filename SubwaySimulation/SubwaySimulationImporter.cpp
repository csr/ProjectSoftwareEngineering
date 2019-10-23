//
// Created by Cesare de Cal on 10/23/19.
//

#include "SubwaySimulationImporter.h"
#include "DesignByContract.h"
#include "tinyxml.h"

using namespace std;

//Auxiliary function for internal use only

const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
  if (pElement == NULL) return "";

  TiXmlNode *elemNode = pElement->FirstChild();
  if (elemNode == NULL) return "";
  TiXmlText* text = elemNode->ToText();
  if(text == NULL) return "";
  return text->Value();
}

// Guardiamo il progetto del professore per vedere come è stato fatto
void parseXMLFile() {
  TiXmlDocument doc;
  if (!doc.LoadFile ("testInput/example.xml")) {
    std :: cerr << doc.ErrorDesc () << std::endl;
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
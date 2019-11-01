#pragma once
//#include <string>
//include cose di TiXML
using std::string
#include <vector>

class Parser {
	
	public:
		TiXmlDocument doc;
		
		// 2 vectors to contain things from parsing -> NB: controllare cosa bisogna importare e dichiarazioni !!!!!!!!!!
		std::vector<Station> stations;
		std::vector<Tram> trams;
		
		int openFile(string fileName);
		int findRoot(TiXmlDocument doc);
		void findChild(TiXmlElement* root, string rootName);
		void findValues(TiXmlElement* elem);
	
}
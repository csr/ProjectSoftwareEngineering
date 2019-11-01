//============================================================================
// Name        : Subway.h
// Author      : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Version     :
// Copyright   : Cesare De Cal, Marco Natali, Veronica Orsanigo
// Description : Subway simulation in C++
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef SubwaySimulation_H
#define SubwaySimulation_H
#include <vector>

class Subway {
	private:
		std::vector<Station> stations;
		std::vector<Tram> trams;
	
	public:
		Subway(){}
		void addStation(Station station);
		void addTram(Tram tram);
		Station& getStations();
		Tram& getTram();
		toString();
};

// Closing of the ``header guard''.
#endif

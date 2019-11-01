#ifndef OUTPUT_H
#define OUTPUT_H
#include "Subway.h"
#include <cstdlib>

class Output{
	public: 
	   Output(){}
	   std::fstream print(std::string fileName, Subway& subwayNetwork);
}
#endif

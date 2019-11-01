#include "Output.h"
#include "Subway.h"
#include <cstdlib>

std::fstream print(std::string fileName, Subway& network){
	fstream* file;
	if !fstream.open(fileName, "a"){
		std::cout << "File not exist" << std::endl
		return nullptr;
	}

	file << network.toString() << std::endl;
	std::cout << network.toString() << std::endl;
	file.close();
	return file;
}

//
// Created by bigboss98 on 23/11/19.
//

#include <fstream>
#include "Output.h"
#include "Subway.h"
#include "SubwaySimulationUtils.h"

void graficalOutput(string fileName, Subway& subway) {
  if(!FileExists(fileName)){
    cout << "Output file doesn't exist";
  }

  ofstream outputStream;
  outputStream.open(fileName);
  for(auto station : subway.getStations()){
    outputStream << station->getName() << "===";
  }
  outputStream << endl;
  outputStream << " ";

  for(auto station : subway.getStations()){
    if(station->isCurrentlyOccupied())
      outputStream << "T   ";
    else
      outputStream << "    ";
  }

  outputStream.close();
}

void simpleOutput(string  fileName, Subway& subway){
  if(!FileExists(fileName)){
    cout << "Output file doesn't exist" << endl;
  }

  ofstream outputStream;
  outputStream.open(fileName);
  outputStream << subway.toString();
  outputStream.close();
}

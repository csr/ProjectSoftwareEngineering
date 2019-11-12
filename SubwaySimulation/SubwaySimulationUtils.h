//============================================================================
// Name        : SubwaySimulationUtils.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================


#ifndef SUBWAYSIMULATION__SUBWAYSIMULATIONUTILS_H_
#define SUBWAYSIMULATION__SUBWAYSIMULATIONUTILS_H_

#include <iostream>

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);

std::string ToString(int i);

// Closing of the ``header guard''.
#endif
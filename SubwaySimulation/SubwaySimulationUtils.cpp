//============================================================================
// Name        : SubwaySimulationUtils.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstdio>
#include <string>
#include <regex>
#include <cstdlib>

using namespace std;

#include "SubwaySimulationUtils.h"

/**
Auxiliary functions for file manipulation.
*/
bool DirectoryExists(const std::string dirname) {
  struct stat st;
  return stat(dirname.c_str(), &st) == 0;
}

bool FileExists(const std::string filename) {
  struct stat st;
  if (stat(filename.c_str(), &st) != 0)
    return false;
  ifstream f(filename.c_str());
  if (f.good()) {
    f.close();
    return true;
  } else {
    f.close();
    return false;
  }
}

bool FileIsEmpty(const std::string filename) {
  struct stat st;
  if (stat(filename.c_str(), &st) != 0) return true; // File does not exist; thus it is empty
  return st.st_size == 0;
}

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
  ifstream leftFile, rightFile;
  char leftRead, rightRead;
  bool result;

  // Open the two files.
  leftFile.open(leftFileName.c_str());
  if (!leftFile.is_open()) {
    return false;
  };
  rightFile.open(rightFileName.c_str());
  if (!rightFile.is_open()) {
    leftFile.close();
    return false;
  };

  result = true; // files exist and are open; assume equality unless a counterexamples shows up.
  while (result && leftFile.good() && rightFile.good()) {
    leftFile.get(leftRead);
    rightFile.get(rightRead);
    result = (leftRead == rightRead);
  };
  if (result) {
    // last read was still equal; are we at the end of both files ?
    result = (!leftFile.good()) && (!rightFile.good());
  };

  leftFile.close();
  rightFile.close();
  return result;
}

string ToString(int x) {
  int length = snprintf( NULL, 0, "%d", x );
  char* buf = new char[length + 1];
  snprintf( buf, length + 1, "%d", x );
  string str( buf );
  delete[] buf;
  return str;
}

// Check if this string is made up of letters ONLY
bool isLettersOnly(string string) {
  for (unsigned int i = 0; i < string.size(); i++) {
    char c = string[i];
    if (!isalpha(c) || isdigit(c) || isspace(c)) {
      return false;
    }
  }
  return true;
}

// Check if a given string is a number
bool IsStringNumber(std::string string) {
  std::regex e ("^-?\\d+");
  return std::regex_match(string, e);
}

// The current specs require all integers to be positive
bool ValidIntegerAttribute(int value) {
  return value >= 0;
}

// The current specs require all string to be non-empty
bool ValidStringAttribute(string string) {
  return !string.empty() && isLettersOnly(string);
}

int GenerateRandomNumber(int a, int b) {
  // Setting seed
  srand(time(nullptr));
  if (a == b)
      return a;
  return rand() % (b - a) + a;
}

string ConvertSecondsToTimeString(int input_seconds) {
  string outputStr = "";

  // Add 12 hours as offset
  int input_seconds_offset = 43200 + input_seconds;

  time_t seconds(input_seconds_offset);
  tm *p = gmtime(&seconds);

  string oldHours = ToString(p->tm_hour);
  std::string paddedHours = std::string(2 - oldHours.length(), '0') + oldHours;

  string oldMinutes = ToString(p->tm_min);
  std::string paddedMinutes = std::string(2 - oldMinutes.length(), '0') + oldMinutes;

  string oldSeconds = ToString(p->tm_sec);
  std::string paddedSeconds = std::string(2 - oldSeconds.length(), '0') + oldSeconds;

  outputStr += paddedHours + ":" + paddedMinutes + ":" + paddedSeconds;
  return outputStr;
}
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "vector"
#include "string"
using namespace std;
//enum TYPES{ALPHA, NUMBER, SPACE, UNKNOWN};

const int MAX_TOKEN_LENGTH = 100;
const int MAX_HEIGHT= 500;
const int MAX_WIDTH = 127;
const int MAX_BUFFER = 1000;
//start states
const int NUMBER_STATE = 0;
const int ALPHA_STATE = 20;
const int SPACE_STATE = 40;
const int UNKNOWN_STATE = 60;

enum TYPES{ALPHA, NUMBER, SPACE, UNKNOWN};




/// @brief: to be used in combination with keyword map
/// to assign a number to each keyword.
enum _Keys {ZERO, SELECT, STAR, FROM, SYMBOL};

#endif // CONSTANTS_H

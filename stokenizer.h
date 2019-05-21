//
// Created by Jack Hou on 2019-05-21.
//

#ifndef DATABASE_STOKENIZER_H
#define DATABASE_STOKENIZER_H

#include <string>
#include <iostream>
#include "constants.h"
#include "token.h"
#include "twoD.h"
#include <sstream>
using namespace std;

class STokenizer
{
public:
    STokenizer();

    STokenizer(char str[]);

    bool done();

    bool more();          //true: there are more tokens



    //---------------
    //extract one token (very similar to the way cin >> works)
    //get_token()
    //extract the longest string that match one of the acceptable token types
    //get alpha, or get number, or get unknown
    //if else. (if not getWord => getNumber ==> if not ==> getSpace, etc...)
    friend STokenizer& operator >> (STokenizer& s, Token& t);

    bool get_token(int start_state, string& _token);

    //the following get functions take care of their own start_state
    //increment _pos by 1
    //get the first character from _buffer

    bool getUnknown(Token& token);

    //make the rest of three look like getUnknown(same format)
    bool getSpace(Token& token);

    //getDouble or getInt
    bool getNumber(Token& token);

    //"name4" ==> "name"
    bool getAlpha(Token& token);

    //set a new string as the input string
    void set_string(char str[]);


private:
    //create table for all the tokens we will recognize
    //                      (e.g. int/doubles, words, etc.)
    //int/double, words, space, unknown
    //int and doubles are both NUMBER
    //words are ALPHA
    //UNKNOWN
    //prepare_table
    void make_table();

    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    int _table[MAX_HEIGHT][MAX_WIDTH];
};


#endif //DATABASE_STOKENIZER_H

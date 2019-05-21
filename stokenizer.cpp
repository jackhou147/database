//
// Created by Jack Hou on 2019-05-21.
//

#include "stokenizer.h"


STokenizer::STokenizer():_pos(0)
{
    make_table();
}

STokenizer::STokenizer(char str[]):_pos(0)
{
    int i=0;
    for(; str[i]!='\0'; i++)
    {
        _buffer[i] = str[i];
    };
    _buffer[i] = '\0';
    make_table();
}

bool STokenizer::done()
{
    return _buffer[_pos] == '\0';
}//true: pos is already at the end of list(no more token to be taken)

//NOT done
bool STokenizer::more(){
    char c = _buffer[_pos];
    return !done();
}            //true: there are more tokens

//-- big three --


//---------------
//extract one token (very similar to the way cin >> works)
//get_token()
//extract the longest string that match one of the acceptable token types
//get alpha, or get number, or get unknown
//if else. (if not getWord => getNumber ==> if not ==> getSpace, etc...)
STokenizer& operator >> (STokenizer& s, Token& t)
{
    if(!s.getNumber(t))
        if(!s.getAlpha(t))
            if(!s.getSpace(t))
                s.getUnknown(t);
    return s;
}

bool STokenizer::get_token(int start_state, string& _token)
{
    /*
     *  It tries to find the longest possible string
     * that will end in a success state.
     * If the function is successful, it will
     * return true after resetting the position to the
     * character following the last acceptable character in
     * the string and storing the extracted string in object token.
    */

    int state = start_state;
    int start_pos = _pos;
    int walker = _pos;
    stringstream ss;
    while(_buffer[walker]!='\0' && _table[state][_buffer[walker]]!=-1)
    {
        state = _table[state][_buffer[walker]];
        if(_table[state][0]!=0)    _pos = walker;
        ++walker;
    }
    if(_table[state][0]==0) return false;

    for(int i=start_pos; i<=_pos;i++)
        ss << _buffer[i];
    _token = ss.str();
    ++_pos;
    return true;


    //"3.1415"
    //if the state is fail AND does not have next state to go, terminate
}



//the following get functions take care of their own start_state
//increment _pos by 1
//get the first character from _buffer

bool STokenizer::getUnknown(Token& token)
{
    string t;
    if(get_token(UNKNOWN_STATE,t)){
        token = Token(t,TYPES::UNKNOWN);
        return true;
    }else
        return false;
}


//make the rest of three look like getUnknown(same format)
bool STokenizer::getSpace(Token& token)
{
    string t;
    if(get_token(SPACE_STATE,t)){
        token = Token(t, TYPES::SPACE);
        return true;
    }else
        return false;

}

//getDouble or getInt
bool STokenizer::getNumber(Token& token)
{
    string t;
    if(get_token(NUMBER_STATE,t)){
        token = Token(t, TYPES::NUMBER);
        return true;
    }else
        return false;
}

//"name4" ==> "name"
bool STokenizer::getAlpha(Token& token)
{
    string t;
    if(get_token(ALPHA_STATE,t)){
        token = Token(t, TYPES::ALPHA);
        return true;
    }else
        return false;
}

//set a new string as the input string
void STokenizer::set_string(char str[])
{
    int i=0;
    for(;str[i]!='\0'; i++)
    {
        _buffer[i] = str[i];
    };
    _buffer[i] = '\0';
    _pos = 0;
}

void STokenizer::make_table()
{

    using namespace _2dArr;
    char DIGITS[10];
    for(int i=0; i<10;i++) DIGITS[i]=char('0'+i);
    char LETTERS[52];
    char SPACE[]= " ";
    int i=65;
    //---fill LETTER list
    for(; i<=90; i++)
        LETTERS[i-65] = char(i);
    for(int j=97; j<=122; j++,i++)
        LETTERS[i-65] = char(j);
    init_table(_table);

//        //doubles:
    mark_fail(_table, 0);            //Mark states 0 and 2 as fail states
    mark_success(_table, 1);         //Mark states 1 and 3 as success states
    mark_fail(_table, 2);
    mark_success(_table, 3);

    mark_cells(0, _table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
    mark_cells(0, _table, '.', '.', 2);  //state [0] --- '.' ------> [2]
    mark_cells(1, _table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]
    mark_cells(1, _table, '.', '.', 2);  //state [1] --- '.' ------> [2]
    mark_cells(2, _table, DIGITS, 3);    //state [2] --- DIGITS ---> [3]
    mark_cells(3, _table, DIGITS, 3);    //state [3] --- DIGITS ---> [3]


    //word
    mark_fail(_table, ALPHA_STATE);  //mark state 20 as fail state for word
    mark_success(_table, ALPHA_STATE+1);    //mark state 21 as fail state for word
    mark_cells(ALPHA_STATE,_table, LETTERS, ALPHA_STATE+1);
    mark_cells(ALPHA_STATE+1,_table, LETTERS,ALPHA_STATE+1);

    //space
    mark_fail(_table, SPACE_STATE);  //mark state 20 as fail state for word
    mark_success(_table, SPACE_STATE+1);    //mark state 21 as fail state for word
    mark_cells(SPACE_STATE,_table, SPACE, SPACE_STATE+1);
    mark_cells(SPACE_STATE+1,_table, SPACE,SPACE_STATE+1);

}

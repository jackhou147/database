#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "constants.h"
#include <iostream>
using namespace std;


class Token
{
public:

    Token();
    Token(string str, int type):_token(str),_type(type){}
    friend ostream& operator <<(ostream& outs, const Token& t)
    {
        outs << "|" << t._token << "|";
        return outs;
    }

    //--getter
    int type()
    {
        return _type;
    }
    string token_str()
    {
        return _token;
    }

    //ex: "ABc" ==> "ALPHA"
    string type_string()
    {
        switch (_type) {
            case TYPES::ALPHA:
                return "ALPHA";
                break;
            case TYPES::NUMBER:
                return "NUMBER";
                break;
            case TYPES::UNKNOWN:
                return "UNKNOWN";
                break;
            case TYPES::SPACE:
                return "SPACE";
                break;
            default:
                break;
        }
    }


private:
    string _token;
    int _type;
};
#endif // TOKEN_H

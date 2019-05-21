//
// Created by Jack Hou on 2019-05-21.
//

#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include "MMap.h"
#include "Map.h"
#include "stokenizer.h"
#include "string"

/**
 * @brief Parser takes a string as input, and generates a Multimap of string/string pairs.
 * @example:        INPUT: "select * from student";
                    OUTPUT:     command     | SELECT
                    FIELDS      | *
                    TABLE_NAME  | STUDENT
                    WHERE       | NO
 */
class Parser {

public:
    //--------------------------------------------------
    //-------------  B I G  T H R E E  -----------------
    //--------------------------------------------------

    /// @brief constructor
    Parser();

    /// @brief destructor
    ~Parser();

    /// @brief: copy constructor
    /// @param other to be copied from.
    Parser(const Parser& other);

    /// @brief assignmetn operator
    /// @param other: to be copied from.
    /// @return: return itself.
    Parser& operator = (const Parser& other);

    //------  C O N S T R U C T O R S -------
    /// @brief constructor with parameter command_str
    /// @param command_str: to be stored in _command_str
    Parser(const string& command_str);

    /// @brief constructor with parameter command_str
    /// @param command_str: char array, to be stored in _command_str
    /// @param length: size of command_str array.
    Parser(char* command_str, int length);


    //--------------------------------------------------
    //-------------  M E T H O D S  --------------------
    //--------------------------------------------------

    /**
     * @brief parses a string of command.
     * @return a multimap of the form shown in class example.
     */
    MMap<string,string> get_parse_tree();

private:
    /// @brief: to be used in combination with keyword map
    /// to assign a number to each keyword.
    enum _Keys {ZERO, SELECT, FROM, STAR };

    /// @example keyword["SELECT"] = SELECT
    Map<string, int> _keyword;

    /// @brief: use this to tokenize the inputted string.
    STokenizer _stk;

    /// @brief: the string to be inputted and tokenized.
    /// @example: "SELECT * FROM STUDENTS"
    char* _command_string;

    /// @brief length of _command_string, which is a char array.
    int _command_string_length;
};


#endif //DATABASE_PARSER_H

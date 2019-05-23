//
// Created by Jack Hou on 2019-05-21.
//

#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include "MMap.h"
#include "Map.h"
#include "stokenizer.h"
#include "string"
#include "constants.h"
#include "twoD.h"
#include "deque"
#include "algorithm"

/**
 * @brief Parser takes a string as input, and generates a Multimap of string/string pairs.
 * @example:        INPUT: "select * from student";
                    OUTPUT:     command     | SELECT
                    FIELDS      | *
                    TABLE_NAME  | STUDENT
                    WHERE       | NO
    @note: Parser class keeps its own
 */
class Parser {

public:
    //--------------------------------------------------
    //-------------  B I G  T H R E E  -----------------
    //--------------------------------------------------

    /// @brief constructor.
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
    Parser(char* command_str);


    //--------------------------------------------------
    //-------------  M E T H O D S  --------------------
    //--------------------------------------------------

    /**
     * @brief parses a string of command.
     * @return a multimap of the form shown in class example.
     */
    MMap<string,string>* get_parse_tree();

    void set_string(char* command_str);

private:

    /// @brief this is the state machine; it needs to be initialized.
    int _table[MAX_HEIGHT][MAX_WIDTH];

    /// @example keyword["SELECT"] = SELECT
    Map<string, int>* _keyword;

    /// @brief: use this to tokenize the inputted string.
    STokenizer* _stk;

    /// @brief: the string to be inputted and tokenized.
    /// @example: "SELECT * FROM STUDENTS"
    char* _command_string;

    /// @brief length of _command_string, which is a char array.
    int _command_string_length;

    /// @brief initialize the _table state machine.

    void _init_key_word_table();


};


#endif //DATABASE_PARSER_H

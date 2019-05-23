//
// Created by Jack Hou on 2019-05-22.
//

#include "SQL.h"

SQL::SQL() {
    _parser = new Parser();
}

SQL::~SQL()
{
    delete _parser;
}


void SQL::run()
{
    char command[] = "SELECT * FROM STUDENT";
    _parser->set_string(command);
    MMap<string,string>* ptree = _parser->get_parse_tree();
    cout << *ptree;

}
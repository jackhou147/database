//
// Created by Jack Hou on 2019-05-22.
//


#ifndef DATABASE_SQL_H
#define DATABASE_SQL_H

#include "Parser.h"

/***
 * @brief
 * @note: keep a map of tables: _tables
 *  "student": Table
 *  _table["student"] = Table("Student"). In coinstructor
 *
 *  run()
 *      command "select * from student"
 *      tokenize
 *      parse it
 *      t.select(Parse_tree, )
 *      t.select_all()
 */
class SQL {
public:
    SQL();
    ~SQL();
    void run();
private:
    Parser* _parser;
};


#endif //DATABASE_SQL_H

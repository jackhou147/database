//
// Created by Jack Hou on 2019-05-21.
//

#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include "Record.h"
#include "BPlusTree.h"
#include "iostream"
#include "vector"
#include "Map.h"
#include "MMap.h"
#include "string"
#include "fstream"
using namespace std;


/***
 * @brief Table class does the following:
 *              1. QUERIES.
 *              2. keeping and maintaining a B+Tree.
 *              3. Using record class to read and write into a binary file.
 *              4. keeping the two tables, one of which is stored on disk(file).
 * @note: one binary file per table object.
 */
class Table {
public:
    //--------------------------------------------------
    //-------------  B I G  T H R E E  -----------------
    //--------------------------------------------------
    Table();

    ~Table();

    Table(const Table& other);

    Table& operator =(const Table& other);


    //--------------------------------------------------
    //-------------  M E T H O D S  --------------------
    //--------------------------------------------------

    /// @brief:
    /// @return
    int insert(const vector<string>& field_vector);

    /// @brief take a record number, read from file and load into record r.
    /// @param recno: record number.
    /// @return: number of bytes that was read in.
    int read(int recno);




private:
    /// @brief: used for reading/writing to file.
    Record r;

    /// @brief: one of the two tables kept in this class;
    /// used for queries.
    Map<string, MMap<string, int>> m;

    /// @brief name of the file in which the table kept by this object is stored.
    char* _fileName;

    /// @brief length of _fileName;
    int _fileName_length;
};


#endif //DATABASE_TABLE_H

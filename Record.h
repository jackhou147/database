//
// Created by Jack Hou on 2019-05-21.
//

#ifndef DATABASE_RECORD_H
#define DATABASE_RECORD_H

#include "fstream"
#include "iostream"

using namespace std;


/// @brief Record class performs reading/writing individual records from a binary file.
/// @note a "record" is a 2D array.
/// @example: record looks like: {"john", "Doe", "35"}, where each component is a char array.
class Record
{

public:
    //----- C O N S T R U C T O R S -----
    Record();
    Record(char str[]);

    /// @brief write to the end of a file.
    /// @param outs
    /// @return:
    long write(fstream& outs);

    /// @brief: read from the file.
    /// @param ins
    /// @param recno: record number. This number
    /// multiplied by MAX will give the precise location of the record to be read.
    /// @return
    long read(fstream& ins, long recno);

    /// @brief insertion operator. For printing.
    /// @param outs
    /// @param r
    /// @return
    friend ostream& operator<<(ostream& outs, const Record& r);
private:

    /// @brief: (MAX*MAX_ROWS) multiplied by record number
    /// will give the location of any record in the file.
    /// @brief maximum number of columns.
    static const int MAX = 10;

    /// @brief Maximum number of rows.
    static const int MAX_ROWS = 10;

    /// @brief record number; used with MAX
    int recno;

    /// @brief array of char arrays like this: {"john", "Doe", "35"}
    char* record[MAX][];
};


#endif //DATABASE_RECORD_H

#ifndef TWOD_H
#define TWOD_H
#include <iostream>
using namespace std;
namespace _2dArr
{
    template< typename T, size_t height, size_t width >
    void print_table( T(&theArray)[height][width]  ) {
        cout << endl <<"--------" << endl;
        for ( int x = 0; x < height; x ++ ) {
            for ( int y = 0; y < width; y++ ) {
                cout << theArray[x][y] << " ";
            };
            cout << endl;
        }
        cout << endl <<"--------" << endl;
    }
    //Fill all cells of the 2d array with -1
    template<class T, size_t height, size_t width>
    void init_table(T(&_table)[height][width])
    {
        for ( int x = 0; x < height; x ++ )
        {
            for ( int y = 0; y < width; y++ ) {
                _table[x][y] = -1;
            };
        }
    }

    //Mark this state (row) with a 1 (success)
    template< typename T, size_t height, size_t width >
    void mark_success(T(&_table)[height][width], int state)
    {
        _table[state][0] = 1;
    }

    //Mark this state (row) with a 0 (fail)
    template< typename T, size_t height, size_t width >
    void mark_fail(T(&_table)[height][width], int state)
    {
        _table[state][0] = 0;
    }





    //true if state is a success state
    template< typename T, size_t height, size_t width >
    bool is_success(T(&_table)[height][width], int state)
    {
        return _table[state][0];
    }


    //Mark a range of cells in the array.
    template< typename T, size_t height, size_t width >
    void mark_cells(int row, T(&_table)[height][width], int from, int to, int state)
    {
        for(int i=from; i<=to; i++)
        {
            _table[row][i] = state;
        }
    }




    //Mark columns represented by the string columns[] for this row
    template< typename T, size_t height, size_t width >
    void mark_cells(int row, T(&_table)[height][width], const char columns[], int state)
    {
        for(int i=0; columns[i]!='\0'; i++)
        {
            char c = columns[i];
//            cout << "c: " << c << endl;
//            cout << "original: " << _table[row][c] << endl;
            _table[row][c] = state;
//            cout << "after: " << _table[row][c] << endl;
        }
    }



    //Mark this row and column
    template< typename T, size_t height, size_t width >
    void mark_cell(int row,  T(&_table)[height][width], int column, int state)
    {
        _table[row][column] = state;
    }


    //----kind of tested above









    //show string s and mark this position on the string:
    //hello world   pos: 7
    //       ^
    void show_string(char s[], int _pos);
}




#endif

//
// Created by Jack Hou on 2019-05-21.
//

#ifndef DATABASE_UTILS_H
#define DATABASE_UTILS_H

#include "iostream"
#include "vector"
#include "algorithm"
#include "fstream"
#include "string"
#include "sstream"
using namespace std;
const int DEBUG = true;

//====================UTILITY FUNCTIONS====================

/// @brief debug print. helper function for debugging
/// @tparam T
/// @param print_me
template <class T>
inline void dprint(T print_me)
{
    if(DEBUG)
        cout << endl << print_me << endl;
}

template <class S>
inline void shift_right(S*& arr, int& size, int index)
{
    assert(index <= size);
    if((index == size))
    {
        S* newArr = new S[size+1];
        for(int i =0; i<size; i++)
            newArr[i] = arr[i];
        arr = newArr;
        size++;
        return;
    }
    else if(index == (size-1))
    {
        shift_right(arr,size,size);
        arr[size-1] = arr[size-2];
        return;
    }
    int i;
    for(i=size-1; i>=index; --i)
    {
        arr[i+1] = arr[i];
    }

    size ++;
}

template <class S>
inline void insert_to_array(S*& arr, int& size, S item, int i=-1)
{
    if(i==-1)   //assume inserting to last spot!
    {
        shift_right(arr, size, size);
        arr[size-1] = item;
    }

    else {
        shift_right(arr, size, i);
        arr[i] = item;
    }
}

inline int Random(int lo, int hi)
{
    int r = rand()%(hi-lo+1)+lo;

    return r;
}

template <class T>
inline void print_vector(const vector<T>& v, ostream& os = cout)
{
    os << "[";
    for (auto i = v.begin(); i != v.end(); ++i)
        os << *i << ',';
    os << "]" << endl;
}

template <typename T>
inline ostream& operator<<(ostream& os, const vector<T>& v)
{
    print_vector(v,os);
    return os;
}

template <typename T>
inline vector<T>& operator+=(vector<T>& lhs, const T& newItem)
{
    lhs.push_back(newItem);
    return lhs;
}


/// @brief find an element in array and return its index
/// @tparam T
/// @param arr
/// @param size
/// @param item
/// @return -1 if not found.
template <class T>
inline int find_in_arr(T* arr, int size, T item)
{
    int answer = -1;
    for(int i=0; i<size; i++)
        if(arr[i] == item)
            answer = i;

    return answer;
}


/// @brief remove an element from array
/// @tparam T
/// @param arr
/// @param size
/// @param item
template <class T>
inline void remove_from_arr(T*& arr, int& size, T item)
{
    int i=find_in_arr(arr, size,item);
    if(i==-1) return;   //not found.
    else{
        memmove(arr + i, arr + i+1, (size - i - 1) * sizeof(int));
        --size;
    }
}

/// @brief return if n is an odd number
/// @param n
/// @return
inline bool odd(int n)
{
    return (n%2 != 0);
}

template<class T>
inline void split_arr(T*& src, int& src_size, T*& dest, int& dest_size)
{
    if(src_size==0) return; //there's nothing to split if it's an empty array.

    if(odd(src_size))
    {
        for(int i=1+(src_size/2); i<src_size; i++)
            insert_to_array(dest, dest_size, src[i]);
        src_size = 1+(src_size/2);
    }
    else{
        //even size
        for(int i=(src_size/2); i<src_size; i++)
            insert_to_array(dest, dest_size, src[i]);
        src_size = (src_size/2);
    }

}

/// @brief [3,4,5] becomes [3,4] and [4,5]. [1,2,3,4] becomes [1,2] and [3,4]
/// @tparam T
/// @param src
/// @param src_size
/// @param dest
/// @param dest_size
/// @note: not tested.
template <class T>
inline void even_split(T*& src, int& src_size, T*&dest, int&dest_size)
{
    //--------------
    bool odd= bool(src_size%2);
    int middle_index= (src_size / 2);

    //---------------
    for(int i=middle_index; i<src_size;i ++)
        insert_to_array(dest,dest_size,src[i], dest_size);
    src_size -= middle_index;
}



template <class T>
inline void print_array(T* arr, int size, ostream& outs = cout, bool newLine = true)
{
    outs << "[";
    for(int i=0; i<size; i++)
    {
        outs << arr[i];
        if(i+1<size)
            outs << ",";
    }

    outs << "]";
    if(newLine) outs << endl;
}

inline void read_int_array(int*& arr, int& size, ifstream& in)
{
    //read in an integer array
    //[1,2,3]
    assert(size == 0);
    string input;

    while(getline(in, input))
    {
        stringstream ss(input);
        int token;
        char junk;

        ss >> junk;

        while(ss >> token)
        {
            insert_to_array(arr, size, token);
            ss >> junk;
        }
    }

}

/// @brief print out an array to a file
/// @tparam T
/// @param arr
/// @param size
/// @param fileName
/// @return
template <class T>
inline bool print_arr_to_file(T* arr, int size, const string& fileName)
{
    ofstream myFile(fileName);
    if(!myFile.is_open()) return false;
    print_array(arr, size, myFile);
    return true;
}

inline bool read_int_arr_from_file(int*& arr, int& size, const string& fileName)
{
    ifstream myFile(fileName);
    if(!myFile.is_open()) return false;
    assert(size == 0);  //MUST BE EMPTY ARRAY
    read_int_array(arr, size, myFile);
    return true;


}

/// @brief generate an integer array and return a pointer to first element
/// @param how_many size of the array
/// @param low
/// @param high
/// @return
inline int* get_int_array(int how_many, int low, int high)
{
    int size = 0;
    int* arr = new int[how_many];
    for(int i=0; i<how_many; i++)
    {
        insert_to_array(arr,size, Random(low, high));
    }

    assert(size == how_many);   //should be

    return arr;
}

/// @brief print a boolean as true/false
/// @param print_me
/// @param outs
inline inline void print_bool(bool print_me, ostream& outs= cout)
{
    if(print_me) outs << "TRUE";
    else outs << "FALSE";
}


/// @brief print out an endl
/// @param outs
inline void newLine(ostream& outs = cout)
{
    outs << endl;
};



/// @brief print out "======"+title
/// @param title
/// @param outs
inline void divider(const string& title="", ostream& outs = cout)
{
    newLine(outs);
    for(int i=0; i<25; i++) cout << "=";
    cout << title;
    newLine(outs);

}

template <class T>
inline void copy_array(T dest[], const T src[],
                int& dest_size, int src_size)
{
    for(int i=0; i<src_size; i++)
        dest[i] = src[i];
    dest_size = src_size;
}//copy src[] into dest[]

template <class S>
inline void shift_left(S*& arr, int& size, int index)
{
    if(!size) return;
    int i;
    for(i=index+1; i<size; ++i)
    {
        arr[i-1] = arr[i];
    }
    size --;
}
template <class T>
inline void delete_item(T data[ ], int i, int& n, T& entry)
{
    entry = data[i];
    shift_left(data,n,i);
}//delete item at index i and place it in entry



/// @brief see if item is contained in array.
/// @tparam T
/// @param arr
/// @param size
/// @param item
/// @return true if found; or false.
template <class T>
inline bool found_in_array(int*& arr, int size, T item)
{
    for(int i=0; i<size; i++)
        if(arr[i] == item)  //found!
            return true;

    return false;   //not found
}

/// @brief merge two arrays.
/// @tparam T
/// @param to   array to merge into. after merging, this array has the content of second array inserted at its end.
/// @param to_size
/// @param from array to merge "from". after merging, this array is empty and can be discarded.
/// @param from_size
/// @example [1,2,3] and [4,5] becomes [1,2,3,4,5] and []
template <class T>
inline void merge_arrays(T*& to, int& to_size, T*& from, int& from_size)
{
    for(int i=0; i<from_size; i++){
        insert_to_array(to, to_size, from[i], to_size); //push to the end of first array
    }
    from_size = 0;
}

/// @brief check if the array is ascendingly sorted.
/// @tparam T
/// @param arr
/// @param size
/// @return
template <class T>
inline bool is_sorted_ascending(T* arr, int size)
{
    for(int i=0; i<size-1; i++)
        if(arr[i] > arr[i+1]) return false;
    return true;
}

/// @brief check if the array is descendingly sorted.
/// @tparam T
/// @param arr
/// @param size
/// @return
template <class T>
inline bool is_sorted_descending(T* arr, int size)
{
    for(int i=0; i<size-1; i++)
    {
        if(arr[i] < arr[i+1]) return false;
    }
    return true;
}








#endif //DATABASE_UTILS_H

//
// Created by Jack Hou on 2019-05-02.
//

#ifndef BTREE_MPAIR_H
#define BTREE_MPAIR_H

#include "ostream"
#include "vector"
#include "utils.h"
using namespace std;

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;


    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K()):key(k){;}


    MPair(const K& k, const V& v)
    {
        key = k;
        value_list.push_back(v);
    }


    MPair(const K& k, const vector<V>& vlist)
    {
        key = k;
        value_list = vlist;
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << "{" <<print_me.key << ":[";
        for (auto i = print_me.value_list.begin(); i != print_me.value_list.end(); ++i)
            outs << *i << ',';
        outs<<"]}";
        return outs;
    }


    MPair& operator =(const MPair<K, V>& rhs)
    {

        key = rhs.key;
        value_list = rhs.value_list;


        return *this;
    }
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key == rhs.key);
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key < rhs.key);
    }

    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs == rhs) || (lhs < rhs);
    }

    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return !(lhs <= rhs);
    }

    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs > rhs) || (lhs == rhs);
    }

    /*
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {

    }*/
};


#endif //BTREE_MPAIR_H

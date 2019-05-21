//
// Created by Jack Hou on 2019-05-01.
//

#ifndef DATABASE_PAIR_H
#define DATABASE_PAIR_H

#include "ostream"
using namespace std;

template<class K, class V>
class Pair
{

public:

    explicit Pair(const K& key=K(), const V value=V()):_key(key),_value(value){;}

    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << "{" << print_me._key << ":" << print_me._value << "}" << endl;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs._key == rhs._key);
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs._key < rhs._key);
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return !(lhs <= rhs);
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs == rhs) || (lhs < rhs);
    }

    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs == rhs) || (lhs > rhs);
    }




    //??
//    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
//    {
//        return rhs;
//    }



    K _key;
    V _value;


};


#endif //DATABASE_PAIR_H

//
// Created by Jack Hou on 2019-05-21.
//

#ifndef DATABASE_MAP_H
#define DATABASE_MAP_H

#include "BPlusTree.h"
#include "Pair.h"

template <class k, class v>
class Map {

public:

    Map():key_count(0){
        _map = BPlusTree<Pair<k,v>>();
    }



    //------ELEMENT ACCESS
    v& operator[] (const k& key)
    {
        //note: if key does not exist, insert it in.
        if(!_map.contains(Pair<k,v>(key,v())))
            insert(key,v());
        return _map.get(Pair<k,v>(key, v()))._value;
    }

    //------MODIFIERS
    /// @brief insertion
    /// @param key
    /// @param value
    void insert(const k& key, const v& value)
    {

        Pair<k,v> p(key,value);
        _map.insert(p);
    }


    friend ostream& operator<<(ostream& outs, const Map<k, v>& print_me){
        outs<<print_me._map<<endl;
        return outs;
    }

private:

    int key_count;
    BPlusTree<Pair<k,v>> _map;

};



#endif //DATABASE_MAP_H

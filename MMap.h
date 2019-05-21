//
// Created by Jack Hou on 2019-05-02.
//

#ifndef BTREE_MULTIMAP_H
#define BTREE_MULTIMAP_H

#include "BPlusTree.h"
#include "MPair.h"
using namespace std;


template <typename K, typename V>
class MMap
{
public:

    MMap(){;}
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it);
        Iterator operator ++(int unused);
        Iterator operator ++();
        MPair<K, V> operator *();
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs);
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs);

    private:
        typename map_base::Iterator _it;
    };


//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const
    {
    }

    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const
    {
        return get(key);
    }
    vector<V>& operator[](const K& key)
    {
        return get(key);
    }

//  Modifiers
    void insert(const K& k, const V& v)
    {
        if(contains(k))
        {
            get(k).push_back(v);
        }else
        {
            MPair<K,V>mp(k,v);
            mmap.insert(mp);
        }
    }
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const
    {
        return mmap.contains(MPair<K,V>(key,V()));
    }


    vector<V> &get(const K& key) const
    {

        MPair<K,V>temp(key,V());
        assert(mmap.contains(temp));
        return mmap.get(temp).value_list;

    }
    vector<V> &get(const K& key)
    {
        MPair<K,V>temp(key,V());

        return mmap.get(temp).value_list;
    }


    Iterator find(const K& key);
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:



    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};


#endif //BTREE_MULTIMAP_H

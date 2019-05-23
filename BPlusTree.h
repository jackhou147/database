//
// Created by Jack Hou on 2019-04-29.
// NOTE: Copy constructor is implemented to only perform a shallow copy.
//  To perform a deep copy where each element of the source is copied, use the
//  method copy_tree() instead.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include "iostream"
#include "iomanip"
#include "string"
#include "utils.h"
#include "sstream"
using namespace std;

/// @brief templated BTree class
template <class T>
class BPlusTree {
public:

    class Iterator{
    public:
        friend class BPlusTree;
        explicit Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it), key_ptr(_key_ptr){}
        Iterator (const Iterator& other){
            /// @brief: copy constructor.
            it = other.it;
            key_ptr = other.key_ptr;
        }

        /// @brief dereference
        /// @return the key.
        T operator *(){
            assert(key_ptr<it->key_count);
            return it->keys[key_ptr];
        }

        /// @brief assignment operator
        /// @param other
        /// @return
        Iterator& operator =(const Iterator& other)
        {
            it = other.it;
            key_ptr = other.key_ptr;
            return *this;
        }

        /// @brief post increment
        /// @param un_used
        /// @return
        Iterator operator++(int un_used){
            //create a copy of the old iterator.
            Iterator old(*this);

            //increment the iterator itself.
            ++(*this);

            //return the old(not incremented) iterator from step 1.
            return old;

        }

        /// @brief pre increment
        /// @note increment key_ptr by 1; if range exceeded after incrementing, go to next(right sibling)
        /// @return
        Iterator operator++(){
            if(key_ptr + 1 < it->key_count)
            {
                //key ptr is within range, then just point to next key.
                key_ptr += 1;
                return *this;
            }else
            {
                // point it to next(which could be NULL).
                it = it->next;
                key_ptr = 0;
                return *this;
            };
        }

        /// @brief two iterators are equal if their trees are equal, and their key_ptr are equal.
        /// @param lhs: left hand side iterator
        /// @param rhs: righ hand side iterator.
        /// @return: true if equal; false otherwise.
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs.key_ptr == rhs.key_ptr && lhs.it == rhs.it;


        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return !(lhs==rhs);
        }

        void print_Iterator(){
            cout << it->keys[key_ptr];
        }

        bool is_null()const {return !it;}

        friend ostream& operator << (ostream& outs, const Iterator& iter)
        {
            if(!iter.is_null())
                outs << iter.it->keys[iter.key_ptr];
            else
                outs << "!NULL ITERATOR!";
            return outs;
        }

        /// @brief
        /// @return: true if can be incremented.
        bool has_next()
        {
            if((key_ptr < it->key_count) || (it->next != NULL)) return true;
            return false;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    /// @brief return a pointer to the very leftmost leaf node.
    /// @return

    Iterator begin();
    /// @brief return a iterator whose it is NULL.
    /// @return
    Iterator end();

//---------------------------------------------------------------------
//            B I G T H R E E
//---------------------------------------------------------------------
    explicit BPlusTree(bool dup=false):dups_ok(dup), key_count(0), child_count(0), next(NULL){
        keys = new T[ORDER-1];
        children = new BPlusTree*[ORDER]
    ;}

    /// @brief initialize with an array
    /// @param arr
    /// @param size
    BPlusTree(T* arr, int size):dups_ok(false),key_count(0),child_count(0)
    {
        for(int i=0; i<size; i++)
            insert(arr[i]);
    }

    BPlusTree(const BPlusTree<T>& other){
        //NOTE: Copy constructor is implemented to only perform a shallow copy.
        //  To perform a deep copy where each element of the source is copied, use the
        //  method copy_tree() instead.

        dups_ok = other.dups_ok;
        key_count = other.key_count;
        child_count = other.child_count;
        delete[] keys;
        keys = new T[key_count];


        for(int i=0; i<key_count; i++)
        {
            keys[i] = other.keys[i];
        }
        for(int i=0; i<child_count; i++)
            children[i] = other.children[i];


    };


    ~BPlusTree(){
        clear_tree();
    }


//---------------------------------------------------------------------
//            I N S E R T I O N  &  R E M O V A L
//---------------------------------------------------------------------

    bool insert(const T &entry);

    bool remove(const T &entry);



//---------------------------------------------------------------------
//            O P E R A T O R S
//---------------------------------------------------------------------
    /// @brief note: this function IS NOT A DEEP COPY. It copies the pointers!
    /// @param other
    /// @return
    BPlusTree<T>&operator =(const BPlusTree<T>& other)
    {
        // clean up the array of pointers
//        for(int i=0; i<child_count; i++)
//            delete children[i];

        // copying from others
        return *(copy_tree(other));
//        dups_ok = other.dups_ok;
//        key_count = other.key_count;
//        child_count = other.child_count;
//        for(int i=0; i<key_count; i++)
//            keys[i] = other.keys[i];
//        for(int i=0; i<child_count; i++)
//            children[i] = other.children[i];
    }


//---------------------------------------------------------------------
//            H E L P E R S
//---------------------------------------------------------------------


    /// @brief: check if the tree contains an entry.
    /// @param entry: item to search for
    /// @return: true if entry can be found in the tree.
    bool contains(const T& entry)const;

    /// @brief
    /// @param entry
    /// @return : a reference to that entry, if found.
    T& get(const T& entry);

    void clear_tree();
    BPlusTree<T> * copy_tree(const BPlusTree<T> &other);

    BPlusTree* get_children(int i);

    /// @brief print information of this tree. Used for debugging purposes
    /// @param my_name
    void print_info(string my_name="");

    /// @brief check if a tree is valid.
    /// @return
    bool is_valid();

    /// @brief if any of the child is not valid, problem_child will be set to that child.
    /// @param problem_tree
    /// @return
    bool is_valid(BPlusTree*& problem_tree);


    bool empty() const;

    /// @brief count the total number of elements in the tree
    /// @return
    int size() const;

    /// @brief gives you a sample tree
    /// assuming this is an integer tree
    void get_smallest(T& entry);        //entry := leftmost leaf
    T get_smallest();   //find the leftmost leaf and return it.
    BPlusTree<T>* get_next();   //getter for next
    void print_leaf_list(ostream& outs=cout);

    /// @brief return an iterator to this key. NULL if not there.
    /// @param entry: key to search for
    /// @return: an iterator that points to the node containing the entry; if not found, NULL
    Iterator find(const T& entry);


private:
//---------------------------------------------------------------------
//            V A R I A B L E S
//---------------------------------------------------------------------

    int key_count; //size of the keys array
    T* keys = new T[ORDER-1];    //every non-leaf node with k children contains k-1 keys.

    int child_count;    //size of the children(child) array
    BPlusTree** children = new BPlusTree*[ORDER];

    const static int MINIMUM_ENTRY_COUNT = 1;
    const static int MAXIMUM_ENTRY_COUNT = 2 * MINIMUM_ENTRY_COUNT;
    const static int ORDER = MAXIMUM_ENTRY_COUNT+1;
    //  every node has at most M children, where ORDER = M
    //  every node has at most M-1 entries/keys.

    bool dups_ok;   //true if duplicate keys are allowed

    BPlusTree<T>* next;  // pointer to next tree


//---------------------------------------------------------------------
//            H E L P E R  M E T H O D S
//---------------------------------------------------------------------

    /// @brief delete the key at index from keys array, then return it.
    /// @param index: the index at which the item to delete is located.
    /// @return: the deleted item;
    T detach_from_keys(int index);

    /// @brief split both the key and children array of child1 and move half into child2.
    /// @param child1: ASSUMED TO BE NON_EMPTY.
    /// @param child2  : ASSUMED TO BE EMPTY.
    void split(BPlusTree*& child1, BPlusTree*& child2);


    //remove element functions:
    bool loose_remove(const T &entry);
    BPlusTree<T> * fix_shortage(int i, bool report = false);
    void remove_smallest(T& entry);

    void remove_biggest(T& entry);
    void rotate_left(int i);
    void rotate_right(int i);
    void merge_with_previous_child(int i);


    //return a pointer to this key. NULL if not there.
    bool is_leaf() const;

    void print(int indent, ostream &outs=cout) const;




    /// @brief return index of the first item >= key
    /// @param key
    /// @return
    /// @note assuming keys array is sorted in ascending order.

    int first_ge(T key) const;

    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me)
    {
        print_me.print(0,outs);
        return outs;
    }



    void fix_excess(size_t i);


    /// @brief only to be used by helper_insert. for any other purposes, use contains() instead.
    /// @param k
    /// @return
    bool helper_contains(const T& k);
    /// @brief helper function to insert a new key into keys array
    /// @param k
    /// @return
    bool helper_insert(const T &k);

    /// @brief  helper functions to insert a new child int children array.
    /// @param child
    /// @return

    bool helper_insert_child(BPlusTree<T> *child, int index);
    bool loose_insert(const T& item);

    /// @brief check if key array has excess amount of entries.
    /// @return
    bool has_excess();


    void print_key_count_of(BPlusTree* node);
    void print_child_count(string my_name="");

    /// @brief helper function used by fix shortage.
    /// @note headless single parent is defined as a node with 0 keys and 1 child.
    void avoid_headless_single_parent();

    //====================================================
    //===== USED BY IS_VALID() TO CHECK IF VALID    ======
    //====================================================

    bool too_many_keys();
    bool too_many_children();
    bool keys_out_of_order();
    bool inappropriate_left_child();
    bool inappropriate_right_child();
    bool too_few_keys();
    bool too_few_children();
    void transfer_left(int i);          //transfer one element LEFT from child i
    void transfer_right(int i);         //transfer one element RIGHT from child i
    BPlusTree<T> * merge_with_next_subset(int i);    //merge subset i with subset i+1
    bool has_left_sibling(int i, BPlusTree<T>*& left_sib);   //given an index, see if children[i] has left sibling
    bool has_right_sibling(int i, BPlusTree<T> *&right_sib);   //given an index, see if children[i] has right sibling
    void set_next(BPlusTree<T>*& _next); //set next to point to _next
    T last_key();   //return the last key

    /// @brief get the last child of this branch.
    /// @return a pointer to the last child.
    BPlusTree<T>* last_child();

    /// @brief: get the smallest/leftmost leaf node of this branch.
    /// @return: a pointer to the smallest leaf node. If leaf, this itself is returned.
    BPlusTree<T>* get_smallest_node();

    /// @brief get the right most/biggest leaf node of this branch.
    /// @return a pointer to the biggest node. If this is leaf, return this itself.
    BPlusTree<T>* get_biggest_node();

    /// @brief check if an item is in leaf list.
    /// @param item
    /// @return
    bool in_leaf_list(T item);
};








//================================================================
//===============       DEFINITIONS            ===================
//================================================================
template <class T>
bool BPlusTree<T>::insert(const T &entry){
    if(!loose_insert(entry))
        return false;
    if(has_excess())
    {
        // fix the excess of top root
        auto temp = new BPlusTree<T>;
        temp->copy_tree(*this);
        clear_tree();
        helper_insert_child(temp,0);
        //...

        fix_excess(0);
    }
    return true;
}                //insert entry into the tree

template <class T>
bool BPlusTree<T>::remove(const T &entry)
{
    if (!loose_remove(entry))
        return false;

    avoid_headless_single_parent();
    return true;
}//remove entry from the tree


/// @brief print the linked list of leaves
template <class T>
void BPlusTree<T>::print_leaf_list(ostream& outs)
{
    auto head = get_smallest_node();
    while(head != 0)
    {
        print_array(head->keys,head->key_count,outs,false);
        head = head->next;
        if(head)
            outs << " => ";
    }
}
/// @brief
/// @param entry: item to search for
/// @return: true if entry can be found in the tree.
template <class T>
bool BPlusTree<T>::contains(const T& entry)const{
    int i = first_ge(entry);
    if(keys[i] == entry)
        return true;
    else if(is_leaf())
        return false;
    else
        return children[i]->contains(entry);
}

template <class T>
T& BPlusTree<T>::get(const T& entry)
{
    //the caller must ensure that the entry is actually in here.
    //given a key, return a reference to it
    assert(contains(entry));
    int i = first_ge(entry);
    if(keys[i] == entry)
        return keys[i];
    else
        return children[i]->get(entry);
}

/// @brief delete/clear each and every node of this tree.
/// @tparam T
template <class T>
void BPlusTree<T>::clear_tree(){

    //------   NOTHING TO DO WITH EMPTY NODES -------
    if(empty()) return;

    //------    1. ZERO OUT KEYS ARRAY.
    key_count = 0;
    //------    2. POINT NEXT TO NULL(NOT DELETE IT)
    next = NULL;
    //------    3. FOR EACH CHILD IN CHILDREN[], LET IT CLEAR ITSELF, THEN DELETE THAT POINTER.
    for(int i=0; i<child_count; i++)
    {
        children[i]->clear_tree();
        delete children[i];
    }
    //------    4. ZERO OUT CHILDREN ARRAY
    child_count = 0;
}

/// @brief given another tree, create a deep copy of it (into yourself)
/// @tparam T
/// @param other: tree to copy from.
template <class T>
BPlusTree<T> * BPlusTree<T>::copy_tree(const BPlusTree<T> &other)
{
//    cout << "copy_tree fired" << endl;
    //------    1. CLEAR YOURSELF UP.
    clear_tree();


    // copy all the keys, whether this is a leaf node or not.
    for(int i=0; i<other.key_count; i++)
        insert_to_array(keys, key_count, other.keys[i]);

    if(other.is_leaf())
        return this;

    // if this is not a leaf node, copy all children,
    // making sure right most node of child1 and leftmode node of child2 are linked.
    BPlusTree<T>* temp;
    BPlusTree<T>* rightMostNode = NULL;
    BPlusTree<T>* leftMostNode = NULL;
    for(int i=0; i<other.child_count; i++)
    {
        temp = new BPlusTree<T>;
        temp->copy_tree(*(other.children[i]));
        helper_insert_child(temp, child_count);
        leftMostNode = temp->get_smallest_node();
        if(rightMostNode != NULL)
            rightMostNode->next = leftMostNode;
        rightMostNode = temp->get_biggest_node();
    }
    return this;

}

template <class T>
BPlusTree<T>* BPlusTree<T>::get_children(int i)
{
    assert(i < child_count);
    auto temp = new BPlusTree<int>;
    temp->copy_tree(*children[i]);
    return temp;
}

/// @brief print information of this tree. Used for debugging purposes
/// @param my_name
template <class T>
void BPlusTree<T>::print_info(string my_name)
{
    BPlusTree<T>* problem;
    cout << endl << "=========info========" << endl;
    cout << "name: " << my_name << endl;
    cout << "key count: " << key_count << endl;
    cout << "key array: ";
    print_array(keys, key_count);
    cout << "child count: " << child_count << endl;
    cout << "valid? " << is_valid(problem) << endl;
    cout << "==============";
    cout << endl << endl;
}

template <class T>
bool BPlusTree<T>::is_valid()
{
    if (is_leaf()) return true;

    //if (data[last item] is NOT <= all subset[last subtree]->data
    // *      return false;
    auto _last_child = last_child();
    T _last_key = last_key();
    for (int i = 0; i < _last_child->key_count; i++) {
        if (_last_key > _last_child->keys[i]) {

            return false;
        }
    }

    // for every data[i]
    // *      if data[i] is NOT > all subset[i]->data
    // *          return false;
    for(int i=0; i<key_count ;i++) {
        T k = keys[i];
        //loop through each key of children[i]
        for (int j = 0; j < children[i]->key_count; j++){
            if (k < children[i]->keys[j])
            {

                return false;
            }
        }

    }

    //for every data[i]
    // *      if data[i] is not in the leaves or children[i] is not valid
    // *          return false;
    // *
    auto left_most = get_smallest_node();
    for(int i=0; i<key_count; i++)
    {
        if(!left_most->in_leaf_list(keys[i]))
        {
            return false;
        }else if(!children[i]->is_valid())
        {

            return false;
        }
    }
    return true;
}

/// @brief if any of the child is not valid, problem_child will be set to that child.
/// @param problem_tree
/// @return
template <class T>
bool BPlusTree<T>::is_valid(BPlusTree*& problem_tree) {
    if (is_leaf()) return true;

    //if (data[last item] is NOT <= all subset[last subtree]->data
    // *      return false;
    auto _last_child = last_child();
    T _last_key = last_key();
    for (int i = 0; i < _last_child->key_count; i++) {
        if (_last_key > _last_child->keys[i]) {
            problem_tree = this;
            return false;
        }
    }

    // for every data[i]
    // *      if data[i] is NOT > all subset[i]->data
    // *          return false;
    for(int i=0; i<key_count ;i++) {
        T k = keys[i];
        //loop through each key of children[i]
        for (int j = 0; j < children[i]->key_count; j++){
            if (k < children[i]->keys[j])
            {
                problem_tree = this;
                return false;
            }
        }

    }

    //for every data[i]
    // *      if data[i] is not in the leaves or children[i] is not valid
    // *          return false;
    // *
    auto left_most = get_smallest_node();
    for(int i=0; i<key_count; i++)
    {
        if(!left_most->in_leaf_list(keys[i]))
        {
            problem_tree = this;
            return false;
        }else if(!children[i]->is_valid())
        {
            problem_tree = children[i];
            return false;
        }
    }

    return true;
}

template <class T>
bool BPlusTree<T>::empty() const
{
    return (key_count == 0) && (child_count == 0);
}//true if the tree is empty


/// @brief count the total number of elements in the tree
/// @return
template <class T>
int BPlusTree<T>::size() const
{
    int counter = key_count;
    for(int i=0; i<child_count; i++)
        counter+=children[i]->size();
    return counter;
}




//================================================================
//=======================   HELPER METHODS =======================
//================================================================

/// @brief delete the key at index from keys array, then return it.
/// @param index: the index at which the item to delete is located.
/// @return: the deleted item;
template <class T>
T BPlusTree<T>::detach_from_keys(int index)
{
    assert(index < key_count);
    T item = keys[index];
    shift_left(keys,key_count,index);
    return item;
}

/// @brief split both the key and children array of child1 and move half into child2.
/// @param child1: ASSUMED TO BE NON_EMPTY.
/// @param child2  : ASSUMED TO BE EMPTY.
template <class T>
void BPlusTree<T>::split(BPlusTree*& child1, BPlusTree*& child2)
{
    assert(
            child1!=0 & child2!=0 &
            !child1->empty()
            & child2->empty()
    );

    //move half of the key array from chidl1 to child2
    split_arr(child1->keys, child1->key_count, child2->keys, child2->key_count);
    //move half of children array from child1 to child2
    split_arr(child1->children, child1->child_count,
              child2->children, child2->child_count);
}


//remove element functions:
template <class T>
bool BPlusTree<T>::loose_remove(const T &entry)
{
    /*
     *        |   !found               |   found                 |
       ------|------------------------|-------------------------|-------
       leaf  |  a: nothing            | b: delete               |
             |     to do              |    target               |
       ------|------------------------|-------------------------|-------
       !leaf | c:                     | d: B_PLUS_TREE          |
             |  [i]->  loose_remove   |   [i+1]-> loose_remove  |
             |  fix_shortage(i)       | fix_shortage(i+1) [...] |
       ------|------------------------|-------------------------|-------
     */

    bool found = found_in_array(keys,key_count, entry);
    int i = first_ge(entry); //-1 if not found.
    int index;

    if(is_leaf())//is leaf
    {
        //a. if !found, nothing to do.
        if(!found)  return false;   //? what to return here ?

            //b. if found, delete it.
        else
        {
            remove_from_arr(keys,key_count, entry);
            return true;
        }
    }else{//not leaf

        //c. if !found, loose remove from children[i]
        if(!found)
        {
            children[i]->loose_remove(entry);
            if(children[i]->too_few_keys())
                fix_shortage(i);
            return true;
        }

            //d. if found, loose remove from children[i+1], then fix shortage of children[i+1]
        else{
            BPlusTree<T>* fixed;
            children[i+1]->loose_remove(entry);
            if(!children[i+1]->empty())
                children[i+1]->get_smallest(keys[i]);
            if(children[i+1]->too_few_keys())
                fixed = fix_shortage(i+1);

            //--------------
            index = find_in_arr(keys, key_count, entry);
            if(index != -1)
            {
                //-----  FOUND   ------
                children[i+1]->get_smallest(keys[i]);

            }else{
                //----- NOT FOUND -----
                index = find_in_arr(children[i]->keys, children[i]->key_count,entry);
                if(index != -1)
                    children[i+1] -> get_smallest(children[i]->keys[index]);
            }
            return true;
        }
    }


}//allows MINIMUM-1 data elements in the root

template <class T>
BPlusTree<T> * BPlusTree<T>::fix_shortage(int i, bool report)
{
    //----------
    BPlusTree<T>* fixed = children[i];
    BPlusTree<T>* left_sibling;
    BPlusTree<T>* right_sibling;
    bool    has_left_sib = has_left_sibling(i,left_sibling),
            has_right_sib = has_right_sibling(i, right_sibling);


    //----------    4 cases   ----------
    if(has_left_sib && left_sibling->key_count > MINIMUM_ENTRY_COUNT)
    {
        transfer_right(i-1);
    }
    else if(has_right_sib && right_sibling->key_count > MINIMUM_ENTRY_COUNT)
    {
        transfer_left(i+1);
    }
    else if(has_left_sib)
    {
        fixed = merge_with_next_subset(i-1);
    }else
    {
        fixed = merge_with_next_subset(i);
    }

    return fixed; //return a pointer to the fixed subset.

}//fix shortage of data elements in child i


template <class T>
void BPlusTree<T>::remove_smallest(T& entry)
{
    assert(key_count > 0);

    entry = keys[0];
    shift_left(keys, key_count, 0);
//        if(!child_count)
//        {
//            entry = keys[0];
//            --key_count;
//        }
//
//        else
//        {
//
//            children[0]->remove_smallest(entry);
//            if(children[0]->too_few_keys())
//                fix_shortage(0);
//        }
}

template <class T>
void BPlusTree<T>::remove_biggest(T& entry)
{
    if(!child_count)
    {
        entry = keys[key_count-1];
        --key_count;
    }

    else
    {
        children[child_count-1]->remove_biggest(entry);
        if(children[child_count-1]->too_few_keys())
            fix_shortage(child_count-1);
    }
}//remove the biggest child of this tree->entry


/// @brief  //transfer one element LEFT from child i
/// @tparam T
/// @param i: index of the child to borrow from.
template <class T>
void BPlusTree<T>::rotate_left(int i)
{
    /*
     * i = 1:
     *              [50 100]
     *  [  ]        [65 75]       ....
     *            [a]  [b]  [c]
     *
     * becomes:
     *
     *            [65 100]
     *  [50]         [ 75 ]       ....
     *     [a]      [b]  [c]
     */
    assert(0 < i && i < child_count && children[i]->key_count > MINIMUM_ENTRY_COUNT);

    T   parent_first_key = keys[i-1],
            new_parent_first_key = children[i]->keys[0];
    auto child_i = children[i], child_before_i = children[i-1];

    //1. FIRST item of subset[i]->data moves up to data to replace data[i-1]
    keys[i-1] = new_parent_first_key;
    shift_left(children[i]->keys, children[i]->key_count,0);


    //2. data[i-1] moves down to the RIGHT of subset[i-1]->data
    children[i-1]->helper_insert(parent_first_key);
    //make sure its to the RIGHT
    assert(children[i-1]->keys[children[i-1]->key_count-1] == parent_first_key);



    //if child_i is not leaf , give its first child to be the last child of child_before_i
    if(!child_i->is_leaf()){
        child_before_i->helper_insert_child(child_i->children[0], child_before_i->child_count);
        shift_left(child_i->children,child_i->child_count,0);   //ignore its first child, since its been pointed to by someone else already.
    }


}

/// @brief  //transfer one element RIGHT from child i
/// @tparam T
/// @param i
template <class T>
void BPlusTree<T>::rotate_right(int i)
{
    assert( i < child_count-1 && children[i]->key_count > MINIMUM_ENTRY_COUNT);
    auto child_i = children[i], child_after_i = children[i+1];
    T   parent_last_key = keys[i],
            new_parent_last_key = child_i->keys[child_i->key_count-1];

    //1. LAST item of subset[i]->data moves up to data to replace data[i],
    keys[i] = new_parent_last_key;
    remove_from_arr(child_i->keys, child_i->key_count, new_parent_last_key);


    //2. data[i] moves down to the LEFT of subset[i+1]->data
    child_after_i->helper_insert(parent_last_key);
    assert(child_after_i->keys[0] == parent_last_key);


    //3. if child_i is not leaf, give its last child to the front of child_after_i
    if(!child_i->is_leaf())
    {
        child_after_i->helper_insert_child(child_i->children[child_i->child_count-1],0);
        child_i->child_count--; //ignore it, since it's been pointed to by someone else already.
    }
}
template <class T>
void BPlusTree<T>::merge_with_previous_child(int i)
{
    //a.
    auto child_before_i = children[i-1];
    auto child_i = children[i];
    //good thru here
    insert_to_array(child_before_i->keys, child_before_i->key_count, keys[i-1]);
    shift_left(keys, key_count, i-1);

    //b.
    //note: [5,6] is not successfully transferred
    for(int j=0; j<child_i->key_count; j++)
        insert_to_array(child_before_i->keys, child_before_i->key_count, child_i->keys[j]);
    for(int j=0; j<child_i->child_count; j++)
    {
        child_before_i->helper_insert_child(child_i->children[j],child_before_i->child_count);
    };

    //c.
    shift_left(children, child_count, i);


}//merge subset i with subset i-1void shift_left(int* arr, int size, int index)



//return a pointer to this key. NULL if not there.

template <class T>
bool BPlusTree<T>::is_leaf() const {return child_count==0;}
template <class T>
void BPlusTree<T>::print(int indent, ostream &outs) const
{


    const int EXTRA_INDENTATION = 5;
    //print the last child first, then print all the rest of the data and children
    if(child_count>key_count)
    {
        children[child_count-1]->print(indent+EXTRA_INDENTATION,outs);
    }
    for(int i=key_count-1; i>=0; i--)
    {
        outs << setw(indent) << " " << keys[i];
        cout << endl;
        if(i < child_count)
            children[i] -> print(indent+EXTRA_INDENTATION, outs);
        cout << endl;
    }







//        const int EXTRA_INDENTATION = 4;
//        size_t i;
//
//        outs << setw(indent) << "";
//
//        for(i = 0; i < key_count; ++i)
//            outs << keys[i] << " ";
//        outs << endl;
//
//        for(i=0; i<child_count; ++i)
//            children[i]->print(indent + EXTRA_INDENTATION);
}

/// @brief return index of the first item >= key
/// @param key
/// @return
/// @note assuming keys array is sorted in ascending order.
template <class T>
int BPlusTree<T>::first_ge(T key) const
{
    bool found = false;
    int i=0;
    while(!found && i < key_count)
    {
        if(keys[i] >= key)
        {
            found = true;
            i--;
        }
        i++;
    }
    return i;   //if the while loops stops at i == key_count, the returned i will simply be key_count
}



template <class T>
void BPlusTree<T>::fix_excess(size_t i) {

    //-----variables
    auto child_i = children[i], child_after_i = new BPlusTree;
    T item;

    //-----process
    //this node's child i has one too many items: 3 steps:
    //0. add a new subset at location i+1 of this node
    helper_insert_child(child_after_i, i+1);
    child_i->set_next(child_after_i);


    //1. split subset[i] (both the subset array and the data array) and move half into
    //      subset[i+1] (this is the subset we created in step 1.)
    split(child_i, child_after_i);

    //2.  bring the last data item of subset[i] and insert
    //      it into this node's data[]
    item = child_i->detach_from_keys(child_i->key_count-1);
    helper_insert(item);


    //3. if subset i is leaf, insert that last element(from step 2) into child_after_i
    if(child_i->is_leaf())
        child_after_i->helper_insert(item);


};





/// @brief only to be used by helper_insert. for any other purposes, use contains() instead.
/// @param k
/// @return
template <class T>
bool BPlusTree<T>::helper_contains(const T& k)
{
    for(int i=0; i<key_count; i++)
        if(keys[i] == k) return true;
    return false;
}
/// @brief helper function to insert a new key into keys array
/// @param k
/// @return
template <class T>
bool BPlusTree<T>::helper_insert(const T &k)
{
    //make a new array instead. don't use the old array cuz it has fixed size

    if(helper_contains(k)) return false;

    int i = first_ge(k);
    insert_to_array(keys,key_count,k,i);
    return true;
}

/// @brief  helper functions to insert a new child int children array.
/// @param child
/// @return

template <class T>
bool BPlusTree<T>::helper_insert_child(BPlusTree<T> *child, int index)
{
    insert_to_array(children, child_count, child,index);
}


template <class T>
bool BPlusTree<T>::loose_insert(const T& item)
{
    // Precondition: The entire B-tree is valid.
    // Postcondition: If entry was already in the set, then the set is unchanged
    // and the return value is false. Otherwise, the entry has been added to the
    // set, the return value is true, and the entire B-tree is still
    // valid EXCEPT that the number of entries in the root of this set might be
    // one more than the allowed maximum.

    int i = first_ge(item);

    bool found = (i<key_count && keys[i] == item);

    if(found)
    {
        if(is_leaf())
        {
            //deal with duplicates. call +
            return false;
        } else{
            children[i+1]->loose_insert(item);
            if(children[i+1]->has_excess())
                fix_excess(i+1);
            return true;
        }
    } else{ //not found
        if(is_leaf())
        {
            insert_to_array(keys, key_count,item, i);
            return true;
        }else{  //not found, not leaf
            children[i]->loose_insert(item);
            if(children[i]->has_excess())
                fix_excess(i);
            return true;
        }
    }
}

/// @brief check if key array has excess amount of entries.
/// @return
template <class T>
bool BPlusTree<T>::has_excess()
{
    return key_count > ORDER-1;
}



template <class T>
void BPlusTree<T>::print_key_count_of(BPlusTree<T>* node)
{
    cout << node->key_count << endl;
}

template <class T>
void BPlusTree<T>::print_child_count(string my_name)
{
    cout << my_name << " child : " << child_count << endl;
}

/// @brief helper function used by fix shortage.
template <class T>
void BPlusTree<T>::avoid_headless_single_parent()
{
//    cout << "avoid headless fired" << endl;
    if ((key_count == 0) && (child_count == 1))
    {

        auto shrink_ptr = new BPlusTree<T>;

        shrink_ptr->copy_tree(*children[0]);
        clear_tree();
        copy_tree(*shrink_ptr);
        delete shrink_ptr;
    }
};


template <class T>
bool BPlusTree<T>::too_many_keys() { return key_count > MAXIMUM_ENTRY_COUNT;}

template <class T>
bool BPlusTree<T>::too_many_children() { return child_count > (MAXIMUM_ENTRY_COUNT+1); }

template <class T>
bool BPlusTree<T>::keys_out_of_order()
{
    bool result = false;
    for(int i=0; i<key_count-1; i++)
        if(keys[i] >keys[i+1]) {
            result = true;
        }
    return result;
}

template <class T>
bool BPlusTree<T>::inappropriate_left_child()
{
    //biggest key of left child is bigger than smallest key of this.
    if(is_leaf())
        return false;
    return children[0]->keys[children[0]->key_count-1] > keys[0];
}
template <class T>
bool BPlusTree<T>::inappropriate_right_child()
{
    //smallest key of right child is smaller than biggest key of this.
    if(is_leaf()) return false;
    auto right_child = children[child_count-1];
    return right_child->key_count > 0 && right_child->keys[0] < keys[key_count-1];
}

template <class T>
bool BPlusTree<T>::too_few_keys()
{
    return key_count < MINIMUM_ENTRY_COUNT;
}

template <class T>
bool BPlusTree<T>::too_few_children()
{
    if(is_leaf()) return false;
    return child_count < (key_count+1);

}

/// @brief get the rightmost leaf of this tree.
/// @tparam T
/// @param entry: to be set equal to leftmost leaf.
template <class T>
void BPlusTree<T>::get_smallest(T& entry)
{
    entry = get_smallest();
}

/// @brief get the leftmost leaf key value of this tree and return it.
/// @tparam T
/// @return
template <class T>
T BPlusTree<T>::get_smallest()
{
    if(is_leaf())
    {
        /// return the smallest(leftmost) key,
        assert(key_count > 0);
        return keys[0];
    }else{
        //------   recurse down  a level -----
        assert(child_count > 0);
        return children[0]->get_smallest();
    }
}


/// @brief transfer one key element left from child i.
/// @tparam T
/// @param i
template <class T>
void BPlusTree<T>::transfer_left(int i)
{
    T temp;
    assert(i<child_count);
    auto child_i = children[i];
    if(!children[i]->is_leaf())
    {
        //-----non leaf: BTree's rotate left
        rotate_left(i);
    }else{
        /*
         *  [7 | 10]
         *        /    |     \
         * [( )]<=[(7) | 8]  [10]
         *
         * 1. transfer subset[i(1)]->data[0] to end of subset[i-1]
         *        [7 | 10]
         *      /    |     \
         *   [7]    [8]   [10]
         *
         * 2. update parent of the transfered subset: data[i-1 (0)] = subset[i(1)]->data[0]
         *
         *        [(8) | 10]
         *      /      |     \
         *   [7]     [(8)]   [10]
         */

        //---- leaf:
        temp = child_i->detach_from_keys(0);
        children[i-1]->helper_insert(temp);
        keys[i-1] = child_i->keys[0];
    }
}


/// @brief transfer one element right from child i.
/// @tparam T
/// @param i
template <class T>
void BPlusTree<T>::transfer_right(int i)
{
    auto child_i  =children[i];
    T temp;
    if(!children[i]->is_leaf())
    {
        //----- non leaf: btree's rotate_right()
        rotate_right(i);
    }else{
        //----- leaf:
        //1. transfer child_i's last key to the left of child_after_i's keys[]
        assert(i+1 < child_count);
        temp = child_i->detach_from_keys(child_i->key_count-1);
        children[i+1]->helper_insert(temp);
        assert(children[i+1]->keys[0] == temp);
        //2. update parent of the transfered child
        keys[i] = temp;
    }

}//transfer one element RIGHT from child i


/// @brief merge child_i with child_after_i.
/// @tparam T
/// @param i
/// @return
/// @note
template <class T>
BPlusTree<T> * BPlusTree<T>::merge_with_next_subset(int i)
{
    assert((i +1) < child_count && i<key_count);
    T temp;
    auto child_i = children[i], child_after_i = children[i+1];
    //--------



    //1. remove data[i] from this object
    assert(i < key_count);
    temp = keys[i];
    shift_left(keys, key_count, i);


    //2. if this is not a leaf, append it to child[i]->keys[]
    if(!child_i->is_leaf()) child_i->helper_insert(temp);

    //3. move all keys from child_after_i to the end of child_i
    merge_arrays(child_i->keys, child_i->key_count, child_after_i->keys, child_after_i->key_count);

    //4. move all children from child_after_i to the end of child_i
    merge_arrays(child_i->children, child_i->child_count, child_after_i->children, child_after_i->child_count);

    //5. delete child_after_i, store in a temp pointer
    shift_left(children, child_count, i+1);

    //6. if this is a leaf, point child_i's next to temp's next
    child_i->next = child_after_i->next;

    //7. delete temp ptr

    //--------
    return child_i;
}//merge subset i with subset i+1


/// @brief given an index i, see if it has a left sibling;
///     if it does, left_sib is set to point to the left sibling
/// @tparam T
/// @param i
/// @param left_sib
/// @return
template <class T>
bool BPlusTree<T>::has_left_sibling(int i, BPlusTree<T> *&left_sib) {
    if(i < 0 || i >= child_count) return false;
    left_sib = children[i-1];
    if(i-1 >= 0) return true;
}

/// @brief same as has_left_sibling, but for right sibling.
/// @tparam T
/// @param i
/// @param right_sib
/// @return
template <class T>
bool BPlusTree<T>::has_right_sibling(int i, BPlusTree<T> *&right_sib) {
    if(i < 0 || i+1 >= child_count) return false;
    right_sib = children[i+1];
    if(i+1 < child_count) return true;
}


/// @brief set pointer next to point to _next
/// @tparam T
/// @param _next: the right sibling
template <class T>
void BPlusTree<T>::set_next(BPlusTree<T>*& _next)
{
    BPlusTree<T>* temp = NULL;
    if(next!=NULL) temp = next;
    next = _next;
    _next->next = temp;
}

template <class T>
BPlusTree<T>* BPlusTree<T>::get_next()
{
    return next;
}

/// @brief return the last key
/// @tparam T
/// @return
template <class T>
T BPlusTree<T>:: last_key()
{
    assert(key_count > 0);
    return keys[key_count -1];
}

template <class T>
BPlusTree<T>* BPlusTree<T>::last_child()
{
    assert(child_count > 0);
    return children[child_count -1];
}

/// @brief see if the item is contained in the leaf
/// @tparam T
/// @param item
/// @return
/// @pre: this must be a leaf node already.
template <class T>
bool BPlusTree<T>::in_leaf_list(T item)
{
    assert(is_leaf());
    //traverse through the leaf list, searching for the item. if not found, return false.
    if(found_in_array(keys, key_count, item)) return true;
    else if(next != NULL) return next->in_leaf_list(item);    //search through the next leaf node.
    else return false;   //this is the end of the list; item is not found.

}


/// @brief get the left most leaf
/// @tparam T
/// @return
template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node()
{
    if(is_leaf()) return this;
    return children[0]->get_smallest_node();
}

template <class T>
BPlusTree<T>* BPlusTree<T>::get_biggest_node()
{
    if(is_leaf()) return this;
    return children[child_count-1]->get_biggest_node();
}






//---------------------------------------------------------------------
//            B E G I N ( )   &   E N D ( )
//---------------------------------------------------------------------


template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    return Iterator(get_smallest_node());
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return Iterator(NULL);
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& entry)//return an iterator to this key. NULL if not there.
{
    /*
    * *  try finding the key in this node.
    *  if found:
    *      if is_leaf: then you're done
    *      else recursively call subset[i+1]->find()
    *  else
    *      recursively call subset[i]->find()
     */

    bool found = found_in_array(keys, key_count, entry);
    int i = first_ge(entry);

    //------- F O U N D -------
    if(found){
        if(is_leaf())
            return *(new Iterator(this, i));
        else{
            return children[i+1]->find(entry);
        }
    }
        //------- N O T  F O U N D -------
    else{
        if(!is_leaf())
            return children[i]->find(entry);
        else
            return *(new Iterator());   //NULL, 0
    }
}




#endif //BTREE_BTREE_H

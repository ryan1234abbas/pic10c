#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>


/**
   Computes the hash code for a string.
   @param str a string
   @return the hash code
*/
size_t hash_code(const std::string& str);

class HashTable;//class linkedlist
class Iterator;
class Node;

class Node
{
private:
    std::string data;
    Node* next;
    friend class HashTable;
    friend class Iterator;
};

class Iterator
{
public:
    /**
       Looks up the value at a position.
       @return the value of the node to which the iterator points
    */
    std::string get() const;
    /**
       Advances the iterator to the next node.
    */
    void next();
    /**
       Compares two iterators.
       @param other the iterator to compare with this iterator
       @return true if this iterator and other are equal
    */
    bool equals(const Iterator& other) const;
    bool operator==(const Iterator& other) const;
    void operator++();
    std::string operator*() const;
private:
    const HashTable* container;
    int bucket_index;
    Node* current;

    friend class HashTable;
};

/**
   This class implements a hash table using separate chaining.
*/
class HashTable
{
public:
    /**
       Constructs a hash table.
       @param nbuckets the number of buckets
    */
    HashTable(size_t nbuckets);

    /**
       Tests for set membership.
       @param x the potential element to test
       @return 1 if x is an element of this set, 0 otherwise
    */
    size_t count(const std::string& x);

    /**
       Adds an element to this hash table if it is not already present.
       @param x the element to add
    */
    void insert(const std::string& x);

    /**
       Removes an element from this hash table if it is present.
       @param x the potential element to remove
    */
    void erase(const std::string& x);

    /**
       Returns an iterator to the beginning of this hash table.
       @return a hash table iterator to the beginning
    */
    Iterator begin() const;

    /**
       Returns an iterator past the end of this hash table.
       @return a hash table iterator past the end
    */
    Iterator end() const;

    /**
       Gets the number of elements in this set.
       @return the number of elements
    */
    size_t size() const;
    /**
    Gets the size of buckets.
    @return the size of buckets
   */
    size_t buckets_size() const;
private:
    std::vector<Node*> buckets;
    size_t current_size;
    double load_factor;
    void grow_if_necessary();
    void rehash(size_t);

    friend class Iterator;
};

#endif
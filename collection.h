//----------------------------------------------------------------------
// Author: S. Bowers
// File:   collection.h
// Date:   Fall 2020
//
// Assumptions:
//
//   1. Collections consist of a set of unique keys, where each key
//      has an associated value. A key together with its value is
//      called a "key-value pair".
//
//   2. Because a collection stores a particular key only once, if a
//      key can be associated with multiple underlying values, then
//      the key must be associated with a list containing the
//      underlying values. Thus, the collection would consist of
//      key-value pairs such that each key's corresponding value is
//      a list.
// 
//   3. A key should only be added into a collection if the key isn't
//      already in the collection. If the same key is added more than
//      once, then the behavior of the collection becomes undefined
//      (in terms of finding and removing keys).
//----------------------------------------------------------------------

 
#ifndef COLLECTION_H
#define COLLECTION_H

#include "array_list.h"


template<typename K, typename V>
class Collection
{
public:

  // default destructor
  virtual ~Collection() {};
  
  // add a new key-value pair into the collection 
  virtual void add(const K& a_key, const V& a_val) = 0;

  // remove a key-value pair from the collection
  virtual void remove(const K& a_key) = 0;

  // find and return the value associated with the key
  // if key isn't found, returns false, otherwise true
  virtual bool find(const K& search_key, V& the_val) const = 0;

  // find and return each key >= k1 and <= k2 
  virtual void find(const K& k1, const K& k2, ArrayList<K>& keys) const = 0;
  
  // return all of the keys in the collection 
  virtual void keys(ArrayList<K>& all_keys) const = 0;

  // return all of the keys in ascending (sorted) order
  virtual void sort(ArrayList<K>& all_keys_sorted) const = 0;

  // return the number of key-value pairs in the collection
  virtual size_t size() const = 0;

};


#endif

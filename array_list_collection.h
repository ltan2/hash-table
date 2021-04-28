#ifndef ARRAY_LIST_COLLECTION_H
#define ARRAY_LIST_COLLECTION_H

#include "collection.h"

template<typename K,typename V>
class ArrayListCollection: public Collection<K,V>
{
public:
void add(const K& a_key, const V& a_val);
void remove(const K& a_key);
bool find(const K& search_key, V& the_val) const;
void find(const K& k1, const K& k2, ArrayList<K>& keys) const;
void keys(ArrayList<K>& all_keys) const;
void sort(ArrayList<K>& all_keys_sorted) const;
size_t size() const;

private:
ArrayList<std::pair<K,V>>kv_list;
};

template<typename K,typename V>
void ArrayListCollection<K,V>::add(const K& a_key, const V& a_val){
std::pair<K,V>p;//create new pair to store key and value
p.first = a_key;
p.second = a_val;
//calls array list add to add the new pair into the end of list
kv_list.add(p);
}

template<typename K,typename V>
void ArrayListCollection<K,V>::remove(const K&a_key){
std::pair<K,V>p;
//loop through to search for the index that matches the key
for(size_t i =0;i<kv_list.size();++i){
bool got = kv_list.get(i,p);//get the pair at this index
if(got == true){
if(p.first == a_key){//compare to see if the key parameter matches the pair's key
bool rem = kv_list.remove(i);//calls array list remove
}
}
}
}

template<typename K,typename V>
bool ArrayListCollection<K,V>::find(const K& search_key, V& the_val) const{
//create an empty pair
std::pair<K,V>p;
bool got = false;
for(size_t i =0;i<kv_list.size();++i){
got = kv_list.get(i,p);//get the pair at this index
if(got == true){
if(p.first == search_key){//compare to see if the key parameter is the same as the pair's key
the_val = p.second;//assign the pair's value to be return via pass by reference
return true;
}
}
}
//key not found
return false;
}

template<typename K,typename V>
void ArrayListCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const{
//ArrayList<std::pair<K,V>>temp_list;
for(size_t i=0;i<kv_list.size();++i){
std::pair<K,V>p;
bool got = kv_list.get(i,p);//get the pair in this index
if(got == true){
if((p.first >= k1)&&(p.first <= k2)){//check to see if the pair'svalue is between k1 and k2
//add to keys array since is in between
keys.add(p.first);
}
}
}
}

template<typename K,typename V>
void ArrayListCollection<K,V>::keys(ArrayList<K>& all_keys) const{
for(size_t i=0;i< kv_list.size();++i){//loop through to get all the keys in the list as long as a pair exist in the index
std::pair<K,V>p;
bool got = kv_list.get(i,p);
if(got == true){
//add it to the all_keys list to be return via pass by reference
all_keys.add(p.first);
}
}
}


template<typename K,typename V>
void ArrayListCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const{
//sort
K value;
ArrayList<K>key_list;//create an array list to store the keys
keys(key_list);//populate the created list with all previous keys
key_list.sort();//sort the list

for(size_t i=0;i<kv_list.size();++i){
key_list.get(i,value);
//get the key of the sorted array and add it to a new all_keys_sorted array
all_keys_sorted.add(value);
}

}


template<typename K,typename V>
size_t ArrayListCollection<K,V>::size()const{
return kv_list.size();
}

#endif

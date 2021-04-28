#ifndef BIN_SEARCH_COLLECTION_H
#define BIN_SEARCH_COLLECTION_H

#include "collection.h"

template<typename K,typename V>
class BinSearchCollection: public Collection<K,V>
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
bool bin_search(const K&key, size_t&index)const;
};
 
template<typename K,typename V>
bool BinSearchCollection<K,V>::bin_search(const K&key,size_t&index)const{
size_t size_arr = kv_list.size();
size_t middle_idx = size_arr/2;
K compareKey;
size_t size_tmp = middle_idx;

//base case
std::pair<K,V>p;

if(size_arr ==0){
index =0;
return false;
}

else{
size_t start =0;
size_t end =size_arr-1;

while(end >= start){
size_t middle_idx = (end+start)/2;
bool got = kv_list.get(middle_idx,p);
if(got == true){
compareKey = p.first;
}
else{
return false;
}
if((got == true)&&(compareKey == key)){
index = middle_idx;
return true;
}

//check first half
if(key < compareKey){
end = middle_idx-1;
index = middle_idx;
}
//check right half
if(key > compareKey){
start = middle_idx +1;
index = start;
}

}
}
return false;
}

template<typename K,typename V>
void BinSearchCollection<K,V>::add(const K& a_key, const V& a_val){
size_t index =0;
std::pair<K,V>p;
p.first = a_key;
p.second = a_val;


bool f = bin_search(a_key,index);
if(index == -1){
index =0;
}
if(index > size() -1){
kv_list.add(p);
}
else{
kv_list.add(index,p);
}
}

template<typename K,typename V>
void BinSearchCollection<K,V>::remove(const K& a_key){
size_t index =0;
bool del = bin_search(a_key,index);

if(del == true){
kv_list.remove(index);
}

}

template<typename K,typename V>
bool BinSearchCollection<K,V>::find(const K& search_key, V& the_val) const{
size_t index;

bool found = bin_search(search_key,index);
if(found == true){

std::pair<K,V>p;
p.first = search_key;
bool got = kv_list.get(index,p);
if(got == true){
the_val = p.second;
return true;
}
}

return false;
}

template<typename K,typename V>
void BinSearchCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const{
//remove any elements in keys
	for(size_t i=0;i<keys.size();++i){
	keys.remove(i);
	}
size_t index;
bool found = bin_search(k1,index); //get first k1 index
for(size_t i=index;i<kv_list.size();++i){
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
void BinSearchCollection<K,V>::keys(ArrayList<K>& all_keys) const{
	//remove any elements in all_keys
	for(size_t i=0;i<all_keys.size();++i){
	all_keys.remove(i);
	}

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
void BinSearchCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const{
keys(all_keys_sorted);
}

template<typename K,typename V>
size_t BinSearchCollection<K,V>::size() const{
int s = kv_list.size();
return s;
}



#endif

#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include "collection.h"

template<typename K,typename V>
class HashTableCollection: public Collection<K,V>
{
public:
HashTableCollection();
HashTableCollection(const HashTableCollection<K,V>*&rhs);
~HashTableCollection();
HashTableCollection& operator=(const HashTableCollection<K,V>* &rhs);
void add(const K& a_key, const V& a_val);
void remove(const K& a_key);
bool find(const K& search_key, V& the_val) const;
void find(const K& k1, const K& k2, ArrayList<K>& keys) const;
void keys(ArrayList<K>& all_keys) const;
void sort(ArrayList<K>& all_keys_sorted) const;
size_t size() const;
size_t min_chain_length();
size_t max_chain_length();
double avg_chain_length();

private:
// the chain (linked list) nodes
struct Node {
K key;
V value;
Node* next;
};
// the (resizable) hash table
Node** hash_table;
// number of k-v pairs stored in the collection
size_t length;
// current number of buckets in the hash table
size_t table_capacity;
// current load factor of the hash table
double load_factor_threshold = 0.75;
// double size and rehash the hash table
void resize_and_rehash();
//make empty
void make_empty();
};

template<typename K,typename V>
HashTableCollection<K,V>::HashTableCollection():table_capacity(16),length(0)
{

  hash_table = new Node *[table_capacity]; // create a new array of pointers
  for(size_t i=0;i<table_capacity;++i){
  hash_table[i] = nullptr; //initialize them to nulptr
  }
}


template<typename K,typename V>
HashTableCollection<K,V>::HashTableCollection(const HashTableCollection<K,V>* &rhs)
  : table_capacity(16), length(0)
{
  // defer to assignment operator
  *this = rhs;
}


// TODO: Finish the remaining functions below
template<typename K,typename V>
HashTableCollection<K,V>::~HashTableCollection(){
make_empty(); // call make empty function to delete all the contents of the array and the array itself
}



template <typename K,typename V>
HashTableCollection<K,V>&HashTableCollection<K,V>::operator=(const HashTableCollection<K,V>  *&rhs){
if(table_capacity > 0){
if(*this != rhs){
this>make_empty();


this->hash_table = new Node * [rhs.table_capacity]; //create a new table of the size equivalent to rhs size
table_capacity = rhs.table_capacity;
length = rhs.length;

for(size_t i =0;i<table_capacity;++i){
this->hash_table[i] = nullptr; //initiallize array pointers to null
}

for(size_t i =0;i<table_capacity;++i){
Node * hlp = rhs.hash_table[i];

	while(hlp != nullptr){
		Node * newNode = new Node;
		newNode->key = hlp->key;
		newNode->value = hlp->value;
		newNode->next = nullptr;

		if(this->hash_table[i] == nullptr){ // if the array at that index points to nullptr
		this->hash_table[i] = newNode;
		newNode->next = nullptr;
		}

		else{
		Node * temp = this->hash_table[i];
		this->hash_table[i] = newNode;
		newNode->next = temp;
		}

		hlp = hlp->next;
	}
}

}
}
return *this;
}


template<typename K,typename V>
void HashTableCollection<K,V>::add(const K& a_key, const V& a_val){
Node * newNode = new Node;
Node * ptr = nullptr;
newNode->key = a_key;
newNode->value = a_val;
newNode->next = nullptr;


//hash a key
std::hash<K>hash_fun;
size_t index = hash_fun(a_key) % table_capacity;

//make sure not out of bounds
if((index < 0)||(index > table_capacity -1)){
return;
}


ptr = hash_table[index];
//add to an empty linked list(i.e pointer in the array index points to null
if(hash_table[index] == nullptr){
hash_table[index] = newNode;
newNode->next = nullptr;
length = length+1;
}
//add to non empty linked list
else{
Node * temp = hash_table[index];
hash_table[index] = newNode;
newNode->next = temp;
length +=1;
}
//resize and rehash if load_factor_threshold is greater than 0.75
double load_factor = avg_chain_length();
if(load_factor > 0.75){
resize_and_rehash();
}


}

template<typename K,typename V>
void HashTableCollection<K,V>::remove(const K& a_key){
Node * ptr = nullptr;
//hash a key

std::hash<K>hash_fun;
size_t index = hash_fun(a_key) % table_capacity;

//check if out of bounds
if((index > table_capacity -1)||(index < 0)){
return;
}

ptr = hash_table[index];
Node * prev = nullptr;
Node * del = nullptr;

//make sure the pointer at the array index is not a null pointer
while(ptr !=nullptr){
if(ptr->key == a_key){
del = ptr;
//delete at front

if(prev == nullptr){
hash_table[index] = ptr->next;
delete del;
length = length-1;
return;
}
//delete at middle
else{
prev->next = ptr->next;
delete del;
length = length-1;
return;
}
}
prev = ptr;
ptr = ptr->next;
} 
//not found
}


template<typename K,typename V>
bool HashTableCollection<K,V>::find(const K& search_key, V& the_val) const{
//hash a key
std::hash<K>hash_fun;
size_t index = hash_fun(search_key) % table_capacity;
Node * ptr = nullptr;

//check if out of bounds
if((index < 0)||(index > table_capacity)){
return false;
}

ptr = hash_table[index];
while(ptr!=nullptr){
if(ptr->key == search_key){
the_val = ptr->value;
return true;
}
ptr = ptr->next;
}
//not found
return false;
}

template<typename K,typename V>
void HashTableCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const{
Node * ptr = nullptr;
for(size_t i=0;i<table_capacity;++i){
ptr =hash_table[i];
//loop through chains
	while(ptr!=nullptr){
	K key = ptr->key;
	if((key >= k1)&&(key <=k2)){
	keys.add(key);
	}
	ptr = ptr->next;
	}
}

}

template<typename K,typename V>
void HashTableCollection<K,V>::keys(ArrayList<K>& all_keys) const{
Node * ptr = nullptr;
//loop through table
for(size_t i=0;i<table_capacity;++i){
ptr =hash_table[i];
//loop through chains
	while(ptr!=nullptr){
	all_keys.add(ptr->key);
	ptr = ptr->next;
	}
}

}

template<typename K,typename V>
void HashTableCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const{
keys(all_keys_sorted);
all_keys_sorted.sort();
}

template<typename K,typename V>
size_t HashTableCollection<K,V>::size() const{

return length;
}

template<typename K,typename V>
size_t HashTableCollection<K,V>::min_chain_length(){
size_t min =max_chain_length();
size_t count = 0;
Node * ptr = nullptr;

for(size_t i=0;i<table_capacity;++i){
ptr =hash_table[i];
count = 0;
//loop through chains
while(ptr!=nullptr){
count++;
ptr = ptr->next;
}

//find minimum
if(count < min){
min = count;
}
}
return min;
}

template<typename K,typename V>
size_t HashTableCollection<K,V>::max_chain_length(){
size_t max = 0;
size_t count =0;
Node * ptr = nullptr;
for(size_t i=0;i<table_capacity;++i){
ptr =hash_table[i];
count = 0;
//loop through chains
while(ptr!=nullptr){
count++;
ptr = ptr->next;
}
if(count > max){
max = count;
}
}
return max;

}

template<typename K,typename V>
double HashTableCollection<K,V>::avg_chain_length(){
size_t total_bucket = 0;
double avg = 0.0;
Node * ptr = nullptr;

for(size_t i=0;i<table_capacity;++i){
if(hash_table[i] != nullptr){
total_bucket++;
}
}
if(table_capacity !=0){
avg = total_bucket / table_capacity;
}
else{
return 0.0;
}

return avg;

}

template<typename K,typename V>
void HashTableCollection<K,V>::make_empty(){
if(table_capacity == 0){
return;
}
if(*hash_table != nullptr){
Node * temp =nullptr;
Node * del = nullptr;

if(table_capacity > 0){
for(size_t i =0;i<table_capacity;++i){
temp = hash_table[i];
//delete every single linked list
while(temp!=nullptr){
del = temp;
temp = temp->next;
delete del;
}                                                                                                                                                              
hash_table[i] = nullptr;
}

//delete array of pointers
delete [] hash_table;
}
table_capacity = 0;
length = 0;
}
}

template<typename K,typename V>
void HashTableCollection<K,V>::resize_and_rehash(){
size_t count =0;
size_t newCapacity = table_capacity * 2;

//resize
Node ** tempTable = new Node *[newCapacity];
for(size_t i=0;i<newCapacity;++i){
  tempTable[i] = nullptr;
  }

//rehash
Node * ptr1 = nullptr;
//copy old table into new table

for(size_t i=0;i<table_capacity;++i){
ptr1 = hash_table[i];
Node * hlp =  nullptr;
   
while(ptr1 != nullptr){
Node * temp = new Node;

//rehash the keys
K a_key = ptr1->key;
std::hash<K>hash_fun;
size_t index = hash_fun(a_key) % (newCapacity);
//deep copy each node
temp->key = ptr1->key;
temp->value = ptr1->value;
temp->next = nullptr;

Node * bucket = tempTable[index];

//add to empty array of pointer index
if(tempTable[index] == nullptr){
tempTable[index] = temp;
temp->next = nullptr;
}
//add to non-empty linked list
else{
hlp = bucket;
tempTable[index] = temp;
tempTable[index]->next = hlp;
}

ptr1 = ptr1->next;
count+=1;
}

}

make_empty();
hash_table = tempTable;
table_capacity = newCapacity;
length = count;

}

#endif

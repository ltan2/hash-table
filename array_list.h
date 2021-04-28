#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "list.h"

template<typename T>
class ArrayList : public List<T>
{
public:
  ArrayList();
  ArrayList(const List<T>& rhs);
  ~ArrayList();
  ArrayList& operator=(const List<T>& rhs);

  void add(const T& item);
  bool add(size_t index, const T& item);
  bool get(size_t index, T& return_item) const;
  bool set(size_t index, const T& new_item);
  bool remove(size_t index);
  size_t size() const;
  void selection_sort();
  void insertion_sort();
  void merge_sort();
  void quick_sort();
  void sort(); 
private:
  T* items;
  size_t capacity;
  size_t length;

  // helper to resize items array
  void resize();
  void merge_sort(size_t start, size_t end);
  void quick_sort(size_t start, size_t end);
   
};


template<typename T>
ArrayList<T>::ArrayList()
  : capacity(10), length(0)
{
  items = new T[capacity];
}


template<typename T>
ArrayList<T>::ArrayList(const List<T>& rhs)
  : capacity(10), length(0), items(nullptr)
{
  // defer to assignment operator
  *this = rhs;
}


// TODO: Finish the remaining functions below
template<typename T>
ArrayList<T>::~ArrayList(){
delete[] items;
items = nullptr;
}

template <typename T>
ArrayList<T>&ArrayList<T>::operator=(const List<T>& rhs){
//delete []items;
if(this!=&rhs){
        delete [] items;
	this = new T[capacity];
	for(size_t count =0;count<capacity;count++){
	this[count] = rhs[count];
	}
}
	return *this;
}

template<typename T>
void ArrayList<T>::add(const T& item){
T*del = items;
	
	if(items == nullptr){
	items = new T[capacity];
	*(items) = item;
	}
	if(length == capacity){ // the array is full
		T*temp = new T[capacity*2]; // make new array with twice the size
		size_t count =0;
		for(count=0;count < length;count++){
		temp[count] = items[count];
		}
		temp[count] = item;
		capacity = capacity*2;
		items = temp;
		length = length+1;
		}
	else{
	items[length] = item;
	length = length+1;
	}

}

template<typename T>
void ArrayList<T>::resize(){

	if(length == capacity){
	T*temp = new T[capacity*2];
	items = temp;
	}
	else{
	T*temp = new T[capacity];
	items = temp;
	}
}


template<typename T>
bool ArrayList<T>::add(size_t index, const T& item){


if(length == capacity){ // capacity is full
	if(index >= length){
	add(item);
	return true;
	}
	else{
	T*temp = new T [capacity*2];
	size_t count =0;
	T* del = items;
	bool push = false;
	for(count =0;count<length+1;count++){
		if(index == count){
			push = true;
			temp[index] = item;
		}
		else{//copy over old list
			if(push == true){
			//move old list one step behind their previous index in new list
			temp[count] = items[count-1];
			}
			else{
			temp[count] = items[count];
			}
		}
	}		
	capacity = capacity*2;
	length = length+1;
	items = temp;
	return true;
	}
}
else{
if(index >= length){
add(item);
return true;
}
else{
T*temp = new T [capacity];
	size_t count =0;
	T* del = items;
	bool push = false;
	for(count =0;count<length+1;count++){
		if(index == count){
			push = true;
			temp[index] = item;
		}
		else{
			if(push == true){
			temp[count] = items[count-1];
			}
			else{
			temp[count] = items[count];
			}
		}
	}		
	length = length+1;
	delete [] del;
	//del = NULL;
	items = temp;
	return true;
}
}
return false;
}

template<typename T>
bool ArrayList<T>::get(size_t index, T& return_item) const{
size_t count =0;
	
if(index >=length){
return false;
}

return_item = items[index];
return true;


}
template<typename T>
bool ArrayList<T>::set(size_t index, const T& new_item){

if(index >= length){
return false;
}

items[index] = new_item;
return true;
}
template<typename T>
bool ArrayList<T>::remove(size_t index){
size_t count =0;
bool remove = false;
T*del = items;
T*temp = new T[capacity];
//cannot remove from empty list
if(length == 0){
return false;
}
//loop through array list
for(count =0;count<length;count++){
      //index found do not add to new list
	if(index == count){
	remove = true;
	}
	else{
		if(remove == true){
                //shift the remaining list one step ahead
		items[count-1] = del[count];
		}
		else{
		items[count] = del[count];
		}
	}
}

length = length-1;
if(remove == true){
return true;
}
else{
return false;
}
}

template<typename T>
size_t ArrayList<T>::size()const{
return length;
}

template <typename T>
void ArrayList<T>::selection_sort(){
size_t i;
size_t j;
size_t min_idx;  
T minValue;
if(length == 0){
return;
}
  
    // Moving through the unsorted array 
    for (i = 0; i < (length-1); i++){
        // Find the minimum element and index in unsorted array  
        min_idx = i; 
	minValue = items[i]; 
        for (j = i+1; j < length; j++){
        if (items[j] < minValue){  
            min_idx = j; 
             minValue = items[j]; 
             }
	}
	 //swap element
            items[min_idx] = items[i];
	    items[i] = minValue;
    } 
}  

template<typename T>
void ArrayList<T>::insertion_sort(){
size_t i;
T key;
size_t j; 
  
    //loop through unsorted area
    for (i = 1; i < length; i++) 
    {  
        key = *(items+i);  
        j = i - 1;  
        //loop through sorted area
        while ((j >= 0) &&(items[j] > key)) 
        {  
           // since larger add to end of key
           items[j+1] = items[j];  
            j = j - 1;  
        }  
        *(items+j+1) = key;  
    }
}

template<typename T>
void ArrayList<T>::merge_sort(){
size_t start =0;
size_t end = length-1;
if(length < 1){
return;
}
merge_sort(start,end);
}

template<typename T>
void ArrayList<T>::merge_sort(size_t start, size_t end){
if(start < end){
size_t mid = (start+end)/2;
merge_sort(start,mid);
merge_sort(mid+1,end);

//merge
T tmp[(end-start)+1];
size_t first1 = start;
size_t first2 = mid + 1;
size_t i = 0;
//check to make sure not out of bounce
if((first1 < 0)||(first1 > end)){
return;
}
if(end < 0){
return;
}

if((first2 > end)||(first2 < 0)){
return;
}

//copy whichever value is smaller first
while((first1 <= mid)&&(first2 <= end)){
//not out of bounce
if((first1 < 0)||(first1 > end)){
break;
}
if((first2 > end)||(first2 < 0)){
break;
}
	if(items[first1] < items[first2]){
	tmp[i++] = items[first1++];
	}
	else{
	tmp[i++] = items[first2++];
	}
}

//copy left array
while(first1 <= mid){
tmp[i++] = items[first1++];
}
//copy array array
while(first2 <= end){
tmp[i++] = items[first2++];
}
//copy from temp array to original array
for(size_t i=0;i<=(end-start);++i){
items[start+i] = tmp[i];
}

}
}

template<typename T>
void ArrayList<T>::quick_sort(){
size_t start = 0;
size_t end = length-1;
quick_sort(start,end);
}

template<typename T>
void ArrayList<T>::quick_sort(size_t start, size_t end){
size_t last_p1 = 0;
//make sure not out of bounce
if(end == -1){
return;
}
if(start > length-1){
return;
}

if(start < end){
	T pivot_val = items[start];
	last_p1 = start;
	for(size_t i = start+1;i <= end;++i){
		if(items[i] < pivot_val){
		last_p1 = last_p1+1;
		//swap
		T temp = items[i];
		items[i] = items[last_p1];
		items[last_p1] = temp;
		}
	}
	
	//swap
	T temp = items[start];
	items[start] = items[last_p1];
	items[last_p1] = temp;
    
        //recursive call
	quick_sort(start,(last_p1-1));
	quick_sort((last_p1+1),end);
}

}

template<typename T>
void ArrayList<T>::sort(){
quick_sort();
}












#endif

// ----------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw6_perf.cpp
// DATE: Fall 2020
// DESC: Performs basic performance tests over the resizable array
// collection implementation and the sorted resizable array collection
// implementation (via binary search). Operations tested are
// specified by an input test number:
//     1 = add 
//     2 = remove
//     3 = find value
//     4 = find range
//     5 = sort
//     6 = statistics
// Output consists of average operation times for different sized
// input lists for both implementations, except for test 6, which
// prints statistics information.
//----------------------------------------------------------------------


#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <string>
#include <cassert>
#include "collection.h"
#include "array_list_collection.h"
#include "bin_search_collection.h"
#include "hash_table_collection.h"

using namespace std;
using namespace std::chrono;

// Test generation params
const int ITERATIONS = 3;       // runs to average
const int SHUFFLINGS = 3;       // amount of "randomness"
  
// Implementation types
const int ARRAYLIST = 0;
const int BINSEARCH = 1;
const int HASHTABLE = 2;

// Helper functions: 
unsigned long sum(unsigned long array[], size_t n);
void create_pairs(pair<string,int> array[], size_t n); 
void print(const Collection<string,int>& coll);
  
// Test cases:
double add(pair<string,int> array[], size_t size, int type);
double remove(pair<string,int> array[], size_t size, int type);
double find_value(pair<string,int> array[], size_t size, int type);
double find_range(pair<string,int> array[], size_t size, int type);
double sort(pair<string,int> array[], size_t size, int type);
void stats(pair<string,int> array[], size_t size, size_t& min, size_t& max, double& avg);


// Test driver:
int main(int argc, char* argv[])
{

  // check command line args
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " test-number (1-6)" << endl;
    exit(1);
  }
  string test_number = argv[1];

  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // create the input data
  pair<string, int> array[50000];
  create_pairs(array, 50000);
  
  // test 1: add operation
  if (test_number.compare("1") == 0) {
    const size_t START =0;            // initial test data size
    const size_t STOP = 35000;         // max test data size
    const size_t STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayListCollection add function\n"
         << "# Column 3 = Avg time for BinSearchCollection add function\n"
         << "# Column 4 = Avg time for HashTableCollection add function\n"
         << "# All times are measured in milliseconds" << endl;
    for (size_t size = START; size <= STOP; size += STEP) {
      double avg1 = add(array, size, ARRAYLIST);
      double avg2 = add(array, size, BINSEARCH);
      double avg3 = add(array, size, HASHTABLE);
      cout << size << " " << (avg1/1000.0) << " "
           << (avg2/1000.0) << " "
           << (avg3/1000.0) << endl;
    }
  }
  // test 2: remove operation
  else if (test_number.compare("2") == 0) {
    const size_t START = 0;            // initial test data size
    const size_t STOP = 35000;         // max test data size
    const size_t STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayListCollection remove function\n"
         << "# Column 3 = Avg time for BinSearchCollection remove function\n"
         << "# Column 4 = Avg time for HashTableCollection remove function\n"
         << "# All times are measured in microseconds" << endl;
    for (size_t size = START; size <= STOP; size += STEP) {
      double avg1 = remove(array, size, ARRAYLIST);
      double avg2 = remove(array, size, BINSEARCH);
      double avg3 = remove(array, size, HASHTABLE);
      cout << size << " " << (avg1/1000.0) << " "
           << (avg2/1000.0) << " "
           << (avg3/1000.0) << endl;
    }
  }
  // test 3: find-value operation
  else if (test_number.compare("3") == 0) {
    const size_t START = 0;            // initial test data size
    const size_t STOP = 35000;         // max test data size
    const size_t STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayListCollection find-value function\n"
         << "# Column 3 = Avg time for BinSearchCollection find-value function\n"
         << "# Column 4 = Avg time for HashTableCollection find-value function\n"
         << "# All times are measured in microseconds" << endl;
    for (size_t size = START; size <= STOP; size += STEP) {
      double avg1 = find_value(array, size, ARRAYLIST);
      double avg2 = find_value(array, size, BINSEARCH);
      double avg3 = find_value(array, size, HASHTABLE);
      cout << size << " " << (avg1/1000.0) << " "
           << (avg2/1000.0) << " "
           << (avg3/1000.0) << endl;
    }
  }
  // test 4: find-range operation
  else if (test_number.compare("4") == 0) {
    const size_t START = 0;            // initial test data size
    const size_t STOP = 35000;         // max test data size
    const size_t STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayListCollection find-value function\n"
         << "# Column 3 = Avg time for BinSearchCollection find-value function\n"
         << "# Column 4 = Avg time for HashTableCollection find-value function\n"
         << "# All times are measured in microseconds" << endl;
    for (size_t size = START; size <= STOP; size += STEP) {
      double avg1 = find_range(array, size, ARRAYLIST);
      double avg2 = find_range(array, size, BINSEARCH);
      double avg3 = find_range(array, size, HASHTABLE);
      cout << size << " " << (avg1/1000.0) << " "
           << (avg2/1000.0) << " "
           << (avg3/1000.0) << endl;
    }
  }
  // test 5: sort operation
  else if (test_number.compare("5") == 0) {
    const size_t START = 0;            // initial test data size
    const size_t STOP = 35000;         // max test data size
    const size_t STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayListCollection sort function\n"
         << "# Column 3 = Avg time for BinSearchCollection sort function\n"
         << "# Column 4 = Avg time for HashTableCollection sort function\n"
         << "# All times are measured in microseconds" << endl;
    for (size_t size = START; size <= STOP; size += STEP) {
      double avg1 = sort(array, size, ARRAYLIST);
      double avg2 = sort(array, size, BINSEARCH);
      double avg3 = sort(array, size, HASHTABLE);
      cout << size << " " << (avg1/1000.0) << " "
           << (avg2/1000.0) << " "
           << (avg3/1000.0) << endl;
    }
  }
  // test 6: statistics information
  else if (test_number.compare("6") == 0) {
    const size_t START = 0;            // initial test data size
    const size_t STOP = 35000;         // max test data size
    const size_t STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Min chain length for HashTableCollection\n" 
         << "# Column 3 = Max chain length for HashTableCollection\n" 
         << "# Column 4 = Avg chain length for HashTableCollection\n" << endl;
    for (size_t size = START; size <= STOP; size += STEP) {
      double avg = 0;
      size_t min = 0;
      size_t max = 0;
      stats(array, size, min, max, avg);
      cout << size << " " << min << " " << max << " " << avg << endl;
    }
  }
  else {
    cerr << "error: invalid test number" << endl;
    exit(1);
  }
}


unsigned long sum(unsigned long array[], size_t n)
{
  unsigned long sum = 0;
  for (size_t i = 0; i < n; ++i)
    sum += array[i];
  return sum;
}

// n must be <= 456,975
void create_pairs(pair<string,int> array[], size_t n)
{
  size_t half = n/2;
  string* keys = new string[n];      
  // init keys (characters between 65 and 90)
  char letter[26];
  for (size_t i = 65; i <= 90; ++i)
    letter[i - 65] = i;
  size_t i1 = 0, i2 = 0, i3 = 0, i4 = 0;
  for (size_t i = 0; i < n; ++i) {
    if (i1 == 26) {i1 = 0; i2++;}
    if (i2 == 26) {i2 = 0; i3++;}
    if (i3 == 26) {i3 = 0; i4++;}
    string str = "";
    str += letter[i4];
    str += letter[i3];
    str += letter[i2];
    str += letter[i1];
    keys[i] = str;
    ++i1;
  }
  // shuffle indexes
  string* pile1 = new string[half];
  string* pile2 = new string[n - half];
  for (size_t i = 0; i < SHUFFLINGS; ++i) {
    for (size_t j = 0; j < half; ++j)
      pile1[j] = keys[j];
    for (size_t j = half; j < n; ++j)
      pile2[j - half] = keys[j];
    size_t k = 0;
    for (size_t j = 0; j < half; ++j) {
      string val1 = pile1[j];
      string val2 = pile2[j];
      keys[k++] = (i % 2) ? val1 : val2;
      keys[k++] = (i % 2) ? val2 : val1;
    }
  }
  // create return array
  for (size_t i = 0; i < n; ++i)
    array[i] = pair<string,int>(keys[i], i + 10);

  delete [] pile1;
  delete [] pile2;
  delete [] keys;
  return;
}

void print(const Collection<string,int>& coll)
{
  cout << "{";
  ArrayList<string> keys;
  coll.keys(keys);
  for (size_t i = 0; i < keys.size(); ++i) {
    string key = "";
    keys.get(i, key);
    cout << key;
    if (i < keys.size() - 1)
      cout << ", ";
  }
  cout << "}\n";
}


double add(pair<string, int> array[], size_t size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<string,int>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<string,int>;
  else if (type == BINSEARCH)
    collection = new BinSearchCollection<string,int>;
  else
    collection = new HashTableCollection<string,int>;    
  for (size_t i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (size_t i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    collection->add(array[size+1].first, array[size+1].second);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    collection->remove(array[size+1].first);
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double remove(pair<string,int> array[], size_t size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<string,int>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<string,int>;
  else if (type == BINSEARCH)
    collection = new BinSearchCollection<string,int>;
  else
    collection = new HashTableCollection<string,int>;    
  for (size_t i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (size_t i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    collection->remove(array[size/2].first);
    auto end = high_resolution_clock::now();
    collection->add(array[size/2].first, array[size/2].second);
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double find_value(pair<string,int> array[], size_t size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<string,int>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<string,int>;
  else if (type == BINSEARCH)
    collection = new BinSearchCollection<string,int>;
  else
    collection = new HashTableCollection<string,int>;    
  for (size_t i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (size_t i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    int val;
    collection->find(array[size/2].first, val);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double find_range(pair<string,int> array[], size_t size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<string,int>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<string,int>;
  else if (type == BINSEARCH)
    collection = new BinSearchCollection<string,int>;
  else
    collection = new HashTableCollection<string,int>;    
  for (size_t i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (size_t i = 0; i < ITERATIONS; ++i) {
    size_t k1 = (size/2) - (size/10);
    size_t k2 = (size/2) + (size/10);
    ArrayList<string> keys;
    auto start = high_resolution_clock::now();
    collection->find(array[k1].first, array[k2].first, keys);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;  
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double sort(pair<string,int> array[], size_t size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<string,int>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<string,int>;
  else if (type == BINSEARCH)
    collection = new BinSearchCollection<string,int>;
  else
    collection = new HashTableCollection<string,int>;    
  for (size_t i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (size_t i = 0; i < ITERATIONS; ++i) {
    ArrayList<string> keys;
    auto start = high_resolution_clock::now();
    collection->sort(keys);
    auto end = high_resolution_clock::now();
    if (keys.size() > 0) 
      for (size_t i = 0; i < keys.size() - 1; ++i) {
        string val1 = "", val2 = "";
        keys.get(i, val1);
        keys.get(i + 1, val2);
        assert(val1 < val2);
      }
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


void stats(pair<string,int> array[], size_t size, size_t& min, size_t& max, double& avg)
{
  HashTableCollection<string,int>* collection = new HashTableCollection<string,int>;
  for (size_t i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  min = collection->min_chain_length();
  max = collection->max_chain_length();
  avg = collection->avg_chain_length();
  delete collection;
}




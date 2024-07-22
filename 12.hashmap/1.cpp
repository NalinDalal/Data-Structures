/*
 * HashMap
*a hash map, often called a hash table, is a common data structure that offers
effective key-value pair storing and retrieval A hashmap is an associative
container that stores elements in a key-value format. It utilizes a hash
function to map keys to indices in an array, known as a bucket. This hashing
technique allows for fast retrieval of values based on their associated keys.

implemented using the unordered_map container

Hash Function-> takes a key as input and returns an index within the range of
the hashmap’s underlying array

Collisions occur when multiple keys generate the same hash value and map to the
same index in the array. soln-> chaining and open addressing

Chaining involves creating a linked list at each bucket to store multiple
key-value pairs for the same key

Open Addressing aims to find alternative locations within the hash map to store
colliding elements. it uses a linear probing
*/

// unordered_map used

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
  // Create a hashmap
  unordered_map<int, string>
      hashmap; // hashmap declared to store key-value pairs, key has int type,
               // value has string type

  // Insert key-value pairss into the hashmap using the insert() function
  hashmap.insert(make_pair(1, "Value 1"));
  hashmap.insert(make_pair(2, "Value 2"));
  hashmap.insert(make_pair(3, "Value 3"));

  // Access values using keys
  std::cout << "Value associated with key 1: " << hashmap[1] << endl;
  cout << "Value associated with key 2: " << hashmap[2] << endl;
  cout << "Value associated with key 3: " << hashmap[3] << endl;

  // Check if a key exists- using the find() function
  if (hashmap.find(4) != hashmap.end()) {
    cout << "Key 4 found!" << endl;
  } else {
    std::cout << "Key 4 not found!" << std::endl;
  }

  // Remove a key-value pair using the erase() function
  hashmap.erase(2);

  // Iterate over key-value pairs
  for (const auto &pair : hashmap) {
    cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
  }

  return 0;
}

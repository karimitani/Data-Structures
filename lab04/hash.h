#include "dictionary.h"

struct HashNode {
	KeyType key;
	DataType data;
	HashNode * next;
};

#define MaxBuckets 1029

class HashDictionary : public Dictionary {
	// Add any member variables you need
	int nElements;
	HashNode * buckets[MaxBuckets];
public:
  // Constructor
  HashDictionary()
  // Hashing function
  int hash(KeyType key);
  // Add a record to the dictionary. Returns false if key already exists
  bool addRecord( KeyType key, DataType record);
  // Find a key in the dictionary and return corresponding record or NULL
  DataType findRecord( KeyType key);
  // Removes one element from the table
  bool removeElement(KeyType key);
  KeyType * keys(int * n);

  // Add other methods you may need
};
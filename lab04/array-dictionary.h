#if !defined ARRAY_DICTIONARY_H
#define ARRAY_DICTIONARY_H

#include "dictionary.h"

struct ArrayDictionaryNode {
	char * key;
	void * data;
};

class ArrayDictionary : public Dictionary {
 protected:
	ArrayDictionaryNode *array;
	int maxNumber;
	int currentNumber;
public:
  // Constructor
  ArrayDictionary();
  
  // Add a record to the dictionary. Returns false if key already exists
  bool addRecord( KeyType key, DataType record);
  
  // Find a key in the dictionary and return corresponding record or NULL
  // Use sequential search
  DataType findRecord( KeyType key);

  // Removes one element from the table
  bool removeElement(KeyType key);

  KeyType * keys(int * n);
};

#endif
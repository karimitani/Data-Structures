#include "array-dictionary.h"

class BinarySearchDictionary : public ArrayDictionary {
  // Add any member variables you need
  bool sorted;
public:
  // Constructor
  BinarySearchDictionary();
  bool addRecord( KeyType key, DataType record);
  DataType findRecord( KeyType key);
  void sort();
  void siftDown(int root, int bottom);
};


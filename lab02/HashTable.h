#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct HashTableVoidEntry {
  const char * _key;
  void * _data;
  HashTableVoidEntry * _next;
};

class HashTableVoid {
 public:
  enum { TableSize = 2039};
  HashTableVoidEntry **_buckets;
  int hash(const char * key);
 public:
  HashTableVoid();
  bool insertItem( const char * key, void * data);
  bool find( const char * key, void ** data);
  bool removeElement(const char * key);
};

class HashTableVoidIterator {
  int _currentBucket;
  HashTableVoidEntry *_currentEntry;
  HashTableVoid * _hashTable;
 public:
  HashTableVoidIterator(HashTableVoid * hashTable);
  bool next(const char * & key, void * & data);
};


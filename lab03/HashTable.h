#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Each hash entry stores a key, object pair
template <typename Data>
struct HashTableTemplateEntry {
    const char * _key;
    Data _data;
    HashTableTemplateEntry * _next;
};

// This is a Hash table that maps string keys to objects of type Data
template <typename Data>
class HashTableTemplate {
 public:
  // Number of buckets
  enum { TableSize = 2039};
  // Array of the hash buckets.
  HashTableTemplateEntry<Data> **_buckets;
  // Obtain the hash code of a key
  int hash(const char * key);
  
 public:
  HashTableTemplate();
  bool insertItem( const char * key, Data data);
  bool find( const char * key, Data * data);
  Data operator[] (const char * &key);
};

template <typename Data> int HashTableTemplate<Data>::hash(const char * key)
{
    int h = 0;
    const char * p = key;
    while (*p) {
        h += *p;
        p++;
    }
    return h % TableSize;
}

template <typename Data> HashTableTemplate<Data>::HashTableTemplate()
{
    _buckets = (HashTableTemplateEntry<Data> **) malloc(TableSize*sizeof(HashTableTemplateEntry<Data>*));
    for ( int i = 0; i < TableSize; i++) {_buckets[i] = NULL;}
}

template <typename Data> bool HashTableTemplate<Data>::insertItem( const char * key, Data data)
{
    int h = hash(key);
    HashTableTemplateEntry<Data> * e = _buckets[h];
    while (e!=NULL) {
        if (!strcmp(e->_key, key)) {
            e->_data = data;
            return true;
        }
        e = e->_next;
    }
    // Entry not found. Add it.
    e = new HashTableTemplateEntry<Data>;
    e->_key = strdup(key);
    e->_data = data;
    e->_next = _buckets[h];
    _buckets[h] = e;
    return false;
}

template <typename Data> bool HashTableTemplate<Data>::find( const char * key, Data * data)
{
    // Get hash bucket
    int h = hash(key);
    HashTableTemplateEntry<Data> * e = _buckets[h];
    while (e!=NULL) {
        if (!strcmp(e->_key, key)) {
            // Entry found
            *data = e->_data;
            return true;
        }
        e = e->_next;
    }
    return false;
}

template <typename Data> Data HashTableTemplate<Data>::operator[] (const char * &key) {
	Data d;
	memset((void*) &d, 0, sizeof(d));
	find(key, &d);
	return d;
}

template <typename Data> bool HashTableTemplate<Data>::removeElement(const char * key)
{
    // Get hash bucket
    int h = hash(key);
    HashTableTemplateEntry<Data> * e = _buckets[h];
    HashTableTemplateEntry<Data> * prev = NULL;
    while (e!=NULL) {
        if (!strcmp(e->_key, key)) {
            // Entry found
            if (prev != NULL) {prev->_next = e->_next;}
            else {_buckets[h] = e->_next;}
            delete e;
            return true;
        }
        prev = e;
        e = e->_next;
    }
    return false;
}

template <typename Data> class HashTableTemplateIterator {
    int _currentBucket;
    HashTableTemplateEntry<Data> *_currentEntry;
    HashTableTemplate<Data> * _hashTable;
  public:
    HashTableTemplateIterator(HashTableTemplate<Data> * hashTable);
    bool next(const char * & key, Data & data);
};

template <typename Data> HashTableTemplateIterator<Data>::HashTableTemplateIterator(HashTableTemplate<Data> * hashTable)
{
    _currentBucket = 0;
    _currentEntry = NULL;
    _hashTable = hashTable;
}

template <typename Data> bool HashTableTemplateIterator<Data>::next(const char * & key, Data & data)
{
  if (_currentEntry != NULL) {
    _currentEntry = _currentEntry->_next;
    if (_currentEntry != NULL) {
      key = _currentEntry->_key;
      data = _currentEntry->_data;
      return true;
    }
  }
  _currentBucket++;
  while (_currentBucket < HashTableTemplate<Data>::TableSize ) {
    if (_hashTable->_buckets[_currentBucket] != NULL) {
      _currentEntry = _hashTable->_buckets[_currentBucket];
      key = _currentEntry->_key;
      return true;
    }
    _currentBucket++;
  }
  return false;
}

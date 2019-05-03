#include "minihttpd.h"
#include "dictionary.h"
#include "array-dictionary.h"
#include "bsearch-dictionary.h"
#include "avl-dictionary.h"

// Types of dictionaries used
enum DictionaryType {
  ArrayDictionaryType,
  HashDictionaryType,
  BinarySearchDictionaryType
};

// Inherits from MiniHTTPD
class SearchEngine : public MiniHTTPD {
  Dictionary * _wordToURLList;
 public:
  SearchEngine( int port, DictionaryType dictionaryType);
  void dispatch( FILE * out, const char * requestLine );
};
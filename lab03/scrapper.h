#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhttp.h"
#include "SimpleHTMLParser.h"
#include "HashTableTemplate.h"

// Stores a URL and the first 100 words
struct URLRecord {
  char * _url;          
  char * _description;  
};

// Used to implement a list of URL indexes of the url array.
struct URLRecordList {
    int _urlRecordIndex;     
    URLRecordList * _next;   
};

class WebCrawler : public SimpleHTMLParser {
    int _maxUrls;
    int _headURL;            
    int _tailURL;            
    URLRecord * _urlArray;               
    HashTableTemplate<int> * _urlToUrlRecord; 
    HashTableTemplate<URLRecordList *> * _wordToURLRecordList; 
    public:
        WebCrawler(int maxUrls, int nurlRoots, const char ** urlRoots);
        void onContentFound(char c);
    	void onAnchorFound(char *url);
        void crawl();
        void writeURLFile(const char * urlFileName);
        void writeWordFile(const char *wordFileName);
};
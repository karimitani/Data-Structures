
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhttp.h"
#include "SimpleHTMLParser.h"

void printUsage()
{
  fprintf( stderr, "  Usage: gethttp [-h|-t|-a] url\n");
  fprintf( stderr, "  Example: gethttp http://www.cs.purdue.edu\n");
}


class HTMLParserPrintContent : public SimpleHTMLParser {
public:
	void onContentFound(char c);
};

void HTMLParserPrintContent::onContentFound(char c) {printf("%c",c);}


class HTMLParserPrintHrefs : public SimpleHTMLParser {
public:
	void onAnchorFound(char * url);
};

void HTMLParserPrintHrefs::onAnchorFound(char * url) {printf("%s\n",url);}

int
main( int argc, char ** argv )
{
  char * option;
  char * url;
  
  if ( argc == 1) {
	  printUsage();
	  exit(1);	  
  }
  else if (argc == 2) {
	  option = "";
	  url = argv[1];
  }
  else { 
	  option = argv[1];
	  url = argv[2];
  }  
  // Process the arguments
  if ( !strcmp(option,"-h") ) {
	  printUsage();
	  exit(1);
  }
  else if ( !strcmp(option,"") ) {
	  int n;
	  char * buffer = fetchHTML( url, &n);
	  if (buffer != NULL) {
		  fwrite(buffer, n, 1, stdout);
	  }
  } else if ( !strcmp(option,"-t") ) {
	  // Eliminate tags
	  int n;
	  char * buffer = fetchHTML( url, &n);
	  if (buffer==NULL) {
		  fprintf(stderr, "*** Cannot open URL\n");
		  exit(1);
	  }
	  HTMLParserPrintContent htmlContent;
	  htmlContent.parse(buffer, n);
  } else if ( !strcmp(option,"-a") ) {
	  // Eliminate tags
	  int n;
	  char * buffer = fetchHTML( url, &n);
	  if (buffer==NULL) {
		  fprintf(stderr, "*** Cannot open URL\n");
		  exit(1);
	  }
	  HTMLParserPrintHrefs htmlHrefs;
	  htmlHrefs.parse(buffer, n);
  }
  if ( *argv == NULL ) {
    printUsage();
    exit(1);
  }
}
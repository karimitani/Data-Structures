#include <stdio.h>

#ifndef OPENHTTP_H
#define OPENHTTP_H

enum {
  MaxURLLength = 512,
  MaxLineLength = 1024
};

FILE *openhttp( const char * url, char * contentType );
char * fetchHTML( const char * url, int * n);

#endif
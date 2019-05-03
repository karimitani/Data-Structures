
#ifndef SIMPLEHTMLPARSER_H
#define SIMPLEHTMLPARSER_H

#include "openhttp.h"

class SimpleHTMLParser {
	int urlAnchorLength;
	char urlAnchor[MaxURLLength];
	bool match(char **b, char *m);
 public:
	SimpleHTMLParser();
	bool parse(char * buffer, int n);
	virtual void onContentFound(char c);
	virtual void onAnchorFound(char * url);
};
#endif
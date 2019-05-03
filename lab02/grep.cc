#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char ** argv)
{
	if ( argc < 2 ) {
		fprintf( stderr, "Usage: mygrep pattern [filename]\n" );
		exit(1);
	}
	const char * pattern = argv[1];
   	FILE * in = stdin;	
	if ( argc > 2 )  {
		const char * fileName = argv[2];
		in = fopen( fileName, "r" );
		if ( in == NULL ) {
			perror("fopen");
			exit(1);
		}	
	}
	const int MaxLineSize = 2048;
	char line[MaxLineSize];
	
	while ( fgets( line, MaxLineSize, in ) != NULL ) {
		if ( strstr( line, pattern ) != 0 ) {
			printf("%s", line );
		}
	}
}

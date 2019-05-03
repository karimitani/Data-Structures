#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "openhttp.h"

int parseURL( const char * url, char * host, int * port, char * document )
{
	const char * httpTag = "http://";
	int lenHttpTag = strlen(httpTag);
	if ( strncmp(url,httpTag, lenHttpTag ) ) {return 1;}
	
	// Get host part
	char * p = (char *) url + lenHttpTag;
	char * q = host;
	int i = 0;
	while ( i < MaxURLLength && *p && *p != '/' && *p != ':' ) {
		*q = *p;
		q++;
		p++;
		i++;
	}
	*q = 0;
	
	// Get port
	*port = 80;
	
	if ( *p == ':' ) {
		p++;
		*port = atoi(p);
		if (*port == 0 || *port < 0 ) {
			*port = 80;
		}
		
		while (*p && *p != '/') {
			p++;
		}
	}
	
	if (*p) {strncpy( document, p, MaxURLLength );}
	else {strcpy( document, "/" );}
	return 0;
}

FILE * openhttp( const char * url, char * contentType )
{
	// Parse url
	char host[MaxURLLength];
	int port;
	char document[MaxURLLength];
	int err = parseURL( url, host, &port, document);
	if ( err ) {
		fprintf( stderr, "bad url \"%s\"\n", url );
		return NULL;
	}
	// Initialize socket address structure
	struct  sockaddr_in socketAddress;
	// Clear sockaddr structure
	memset((char *)&socketAddress,0,sizeof(socketAddress));
	// Set family to Internet 
	socketAddress.sin_family = AF_INET;
	// Set port
	socketAddress.sin_port = htons((u_short)port);
	// Get host table entry for this host
	struct  hostent  *ptrh = gethostbyname(host);
	if ( ptrh == NULL ) {
		perror("gethostbyname");
		return NULL;
	}
	// Copy the host ip address to socket address structure
	memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);
	
	// Get TCP transport protocol entry
	struct  protoent *ptrp = getprotobyname("tcp");
	if ( ptrp == NULL ) {
		perror("getprotobyname");
		return NULL;
	}
	// Create a tcp socket
	int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sock < 0) {
		perror("socket");
		return NULL;
	}
	// Connect the socket to the specified server
	if (connect(sock, (struct sockaddr *)&socketAddress,
		    sizeof(socketAddress)) < 0) {
		perror("connect");
		return NULL;
	}
	// Form request
	char * request = (char *) malloc( 50 + strlen(host) + strlen(document) );
	if ( request == NULL ) {
		perror("malloc");
		return NULL;
	}
	//sprintf( request, "GET http://%s%s HTTP/1.0\r\n\r\n", host, document );
	sprintf( request, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", document, host );
	// Send HTTP request
	write( sock, request, strlen(request) );
	write(1, request, strlen(request) );
	free( request );
	// Make a buffered stream from the socket to speed up reading
	FILE * f = fdopen( sock, "r" );
	if ( f == NULL ) {
		perror("fdopen");
		close(sock);
		return NULL;
	}
	// Get everything up to the start of document
	char line[ MaxLineLength ];
	int contentTypeFound = 0;
	const char * contentTypeTag = "Content-Type: ";
	int contentTypeTagLen = strlen( contentTypeTag );
	while ( fgets( line, MaxLineLength, f ) ) {
		if ( !strncmp( line, contentTypeTag, contentTypeTagLen )) {
			contentTypeFound = 1;
			break;
		}
	}
	// Check if content type is there
	if ( !contentTypeFound || strlen(line) == contentTypeTagLen ) {
		fprintf( stderr, "No Content-Type\n");
		close(sock);
		return NULL;
	}
	// Copy content type
	strcpy(contentType, line + contentTypeTagLen);
	// Remove trailer space chars from content type 
	int contentTypeLen = strlen(contentType);
	char * p = contentType + contentTypeLen - 1;
	while ( contentTypeLen > 0 &&
		*p && (*p == ' ' || *p == '\n' || *p == '\r' )) {
		*p = 0;
		p--;
	}
	p = contentType;
	while ( *p && *p!=';') {
		p++;
	}
	if (*p == ';') {
		*p = 0;
	}
	// Return stream file
	return f;
}

char * fetchHTML( const char * url, int * n)
{
	// Open URL
	char contentType[ MaxLineLength ];
	FILE * f = openhttp( url, contentType );
	if ( f == NULL ) {
		return NULL;
	}
	if (strcmp(contentType, "text/html")!=0) {
		printf("Content Type %s not text/html. Type: %s\n", url, contentType);
		fclose(f);
		return NULL;
	}
	// Allocate an initial buffer
	int memIncrement = 8 * 1024;
	int maxBuffer = memIncrement;
	char * buffer = NULL;
	if (buffer == NULL) {
		buffer = (char *) malloc( maxBuffer );
		if (buffer == NULL) {
			perror("malloc");
			return NULL;
		}
	}
	int l;
	*n = 0;
	while ( (l=fread( buffer + *n, 1, maxBuffer - *n, f)) > 0) {
		*n += l;
		if ( maxBuffer - *n == 0 ) {
			maxBuffer += memIncrement;
			buffer = (char *) realloc(buffer, maxBuffer);
		}
	}	
	if ( *n < 0) {
		fclose(f);
		free(buffer);
		return NULL;
	}
	fclose( f );
	return buffer;
}
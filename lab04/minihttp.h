#include <stdio.h>
t. Kill the server when not in use. Do not leave it running.
//
class MiniHTTPD {
  int _port;
 public:
  // Create a new instance of the HTTP server
  MiniHTTPD( int port );
  virtual void dispatch( FILE * out, const char * documentRequested );
  // Wait for incoming requests. The method never returns
  void run();
};
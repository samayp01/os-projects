#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define UNITY_ID "sgpiduru"

#define BUFFER_SIZE 1024

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( EXIT_FAILURE );
}

// Print a short usage message, then exit.
static void usage() {
  fprintf( stderr, "usage: <host> <port> <path>\n" );
  exit( EXIT_FAILURE );
}

/** Simple program to send a request of http1.0 and report the
    response. */
int main( int argc, char *argv[] ) {
  if ( argc != 4 )
    usage();
  
  char *host = argv[ 1 ];
  char *port = argv[ 2 ];
  
  // For getaddrinfo(), tell the system what kinds of addresses we want
  struct addrinfo addrCriteria = {
    .ai_family = AF_UNSPEC,     // Use either IPV4 or IPV6
    .ai_socktype = SOCK_STREAM, // Use byte stream
    .ai_protocol = IPPROTO_TCP  // Use TCP
  };

  // Lookup a list of matching addresses
  struct addrinfo *servAddr;
  if ( getaddrinfo( host, port, &addrCriteria, &servAddr ) != 0 )
    fail( "Can't get address info" );

  // Try to just use the first address we get back, make sure we got one.
  if ( servAddr == NULL )
    fail( "Can't get address" );

  // Make a socket with parameters (e.g., IPV4 vs IPV6) from getaddrinfo()
  int sock = socket( servAddr->ai_family, servAddr->ai_socktype,
                     servAddr->ai_protocol );
  if ( sock < 0 )
    fail( "Can't create socket" );

  // Connect this socket to the server.
  if ( connect( sock, servAddr->ai_addr, servAddr->ai_addrlen ) != 0 )
    fail( "Can't connect to server" );

  // We're done wiht the address info now.
  freeaddrinfo(servAddr);

  // Construct the header for the request.////////////
  // ...
  char *path = argv[ 3 ];
  int paramsSize = strlen( path ) + strlen(host) + strlen(port) + strlen(UNITY_ID);
  char *request = malloc( sizeof(char) * (paramsSize + 100) );

  // sprintf( 
  //   request, 
  //   "GET %s HTTP/1.0\r\nHost: %s:%s\r\nUser-Agent: CSC 246 class %s@ncsu.edu\r\nAccept: */*\r\n\r\n", 
  //   path, host, port, UNITY_ID
  // );

  // do the above with snprintf() instead of sprintf().
  // ...
  snprintf( 
    request, 
    paramsSize + 100, 
    "GET %s HTTP/1.0\r\nHost: %s:%s\r\nUser-Agent: CSC 246 class %s@ncsu.edu\r\nAccept: */*\r\n\r\n",
    path, host, port, UNITY_ID
  );

  // Send the request to the server.//////////////////
  // ...
  if ( write( sock, request, strlen( request ) ) < 0 )
    fail( "Can't send request" );

  // Read back and print out the response.////////////
  // ... 
  char buf[ BUFFER_SIZE ];
  int n;

  // store the response in a string
  char *response = malloc( sizeof(char) * BUFFER_SIZE);
  int responseSize = 0;

  while ( (n = read( sock, buf, BUFFER_SIZE )) > 0 ) {
    responseSize += n;
    response = realloc( response, sizeof(char) * responseSize );
    strncat( response, buf, n );
  }

  // print the response until '\r\n\r\n'
  char *endOfHeader = strstr( response, "\r\n\r\n" );
  int headerSize = endOfHeader - response;
  char *header = malloc( sizeof(char) * (headerSize + 1) );
  strncpy( header, response, headerSize );
  header[ headerSize ] = '\0';

  // print the header to standard error
  fprintf( stderr, "%s\r\n\r\n", header + 6 );

  // print the body to standard output
  printf( "%s", endOfHeader + 4 );
  
  
  // Close the socket connection
  close( sock );

  return 0;
}

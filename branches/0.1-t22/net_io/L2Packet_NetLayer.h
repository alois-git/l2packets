#ifndef H_L2P_NET_LAYER
#define H_L2P_NET_LAYER

/** Initializes L2Packets network layer.
 ** By default network functions L2PNet_* will be used,
 ** which use corresponding Winsock2 functions.
 ** returns 1 on success, 0 on error */
int L2PNet_InitDefault();

/** Closes winsock (wrapper around WSACleanup() **/
int L2PNet_Cleanup();

/** Overrides specified function for L2Packets network layer.
 ** New function must have the same prototype as corresponding
 ** L2PNet_* function! */
#define L2PFUNC_CONNECT       1
#define L2PFUNC_SEND          2
#define L2PFUNC_RECV          3
#define L2PFUNC_SHUTDOWN      4
#define L2PFUNC_CLOSESOCKET   5
#define L2PFUNC_BIND          6
#define L2PFUNC_ACCEPT        7
#define L2PFUNC_SELECT        8
#define L2PFUNC_SOCKET        9
#define L2PFUNC_LISTEN        10
void L2PNet_setFunction( int funcNo, void *func_addr );

/** Creates TCP socket
 ** returns 0xFFFFFFFF on error, on success - [1..0xFFFFFFFE] :) */
unsigned int L2PNet_TCPsocket_create( bool bUse_NonBlock_IO_Mode );

/** Waits for socket to be ready for read or write
 ** returns 1 on success, 0 on timeout, -1 on error */
#define L2PNET_SELECT_READ  0x000000001
#define L2PNET_SELECT_WRITE 0x000000002
int L2PNet_select( unsigned int sock,            // socket descriptor
				  unsigned int dwSelFlags,       // flags what to wait for: L2PNET_SELECT_READ/WRITE
				  long lWaitMilliSecs,           // wait timeout in milliseconds
				  int *pbReadyForRead,           // will be 1, if ready to read, 0 otherwise (may be NULL)
				  int *pbReadyForWrite );        // will be 1, if ready to write, 0 otherwise (mya be NULL)

/** Check state for multiple sockets */
int L2PNet_select_multi( unsigned int *socks_array,    // socket descriptors array
						unsigned int socks_count,      // socket descriptors array item count
						unsigned int dwSelFlags,       // flags what to wait for: L2PNET_SELECT_READ/WRITE
						long lWaitMilliSecs,           // wait timeout in milliseconds
						int *pbReadyForRead,           // array! will be 1, if ready to read, 0 otherwise
						int *pbReadyForWrite );        // array! will be 1, if ready to write, 0 otherwise

/** Receives data from socket.
 ** returns number of bytes read, 0 on connection closed, -1 on error */
int L2PNet_recv( unsigned int sock, unsigned char *pucRecvBuffer, unsigned int uBufferSizeBytes );

/** Writes data to socket.
 ** returns number of bytes sent, -1 on error */
int L2PNet_send( unsigned int sock, const unsigned char *pucSendBuffer, unsigned int uNumberOfBytesToSend );

/** Stops data transfer on socket, preparing to close. */
int L2PNet_shutdown( unsigned int sock );

/** Closes socket and frees its resources from system. */
int L2PNet_closesocket( unsigned int sock );

/** Connects socket to specified address
 ** returns -1 on error/timeout, 0 on error */
int L2PNet_connect( unsigned int sock, const char *ip, unsigned short port );

/** Binds socket to specified address
 ** returns 0 on ok, -1 on error */
int L2PNet_bind( unsigned int sock, const char *ip, unsigned short port );

/** Starts listening on socket to aceept incoming connections
 ** returns 0 on ok, -1 on error */
int L2PNet_listen( unsigned int sock );

/** Accepts incoming connection from socket
 ** returns accepted socket on OK, -1 on error */
unsigned int L2PNet_accept( unsigned int sock, char *acceptedIP, unsigned short *acceptedPort );

/** Wrapper around standard select() function **/
/** !!! CANNOT BE OVERRIDED !!! **/
int L2PNet_select_wrapper_DUMB( int nfds,
						  fd_set *readFds,
						  fd_set *writeFds,
						  fd_set *exceptFds,
						  const struct timeval *timeout );

/** Wrapper around WSAGetLastError() **/
int L2PNet_WSAGetLastError(void);

/** Wrapper around WSASetLastError() **/
void L2PNet_WSASetLastError( int iError );

/** Prints Winsock error code as string to specified file **/
// incomplete errors list!!!!
int L2PNet_WSAPrintLastError( FILE *f, int wsaerr );



//
// Winsock2 functions duplications
//

unsigned long L2PNet_htonl( unsigned long hostlong );
unsigned short L2PNet_htons( unsigned short hostshort );
unsigned long L2PNet_ntohl( unsigned long netlong );
unsigned short L2PNet_ntohs( unsigned short netshort );


/** FUNCTION: Converts a string containing an IPv4 address to an unsigned long
 ** ARGUMENTS:
 **     cp = Pointer to string with address to convert
 ** RETURNS:
 **     Binary representation of IPv4 address, or INADDR_NONE */
unsigned long L2PNet_inet_addr( const char *cp );

/* this function is not thread-safe now -_- */
char *L2PNet_inet_ntoa( struct in_addr in );

/* FD_ISSET macro replacement */
int L2PNet_FD_ISSET( unsigned int sock, struct fd_set *set );

#endif /* H_L2P_NET_LAYER */

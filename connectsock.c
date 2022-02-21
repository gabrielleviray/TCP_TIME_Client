/* connectsock.c - forms connections - allocate a socket and establishes a connection */
/* from textbook: page 63 & 64 */

#define __USE_BSD 1

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif /* INADDR_NONE */

typedef unsigned short u_short;
#include <errno.h>

extern int errexit(const char *format, ...);

/*
* Arguments:
* host - name of host to which connection is desired
* service - service associated with the desired port
* transport - name of transport protocol to use ("tcp" or "udp")
*/

int connectsock(const char *host, const char *service, const char *transport )
{
	// Define structures needed for host info, service info, protocol information, endpoint address
	struct hostent *phe;
	struct servent *pse;
	struct protoent *ppe;
	struct sockaddr_in sin;

	/* create variables for socket descriptor and socket type */
	int s, type;

	memset(&sin, 0, sizeof(sin));

	/* store AF_INET for the family */
	sin.sin_family = AF_INET;

	/* Map service name to port number */
	if ( pse = getservbyname(service, transport) )
	    sin.sin_port = pse->s_port;
	else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 )
	    errexit("can't get \"%s\" service entry\n", service);

	 /* Map host name to IP address, allowing for dotted decimal */
	if ( phe = gethostbyname(host) )
	    memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
	else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
	    errexit("can't get \"%s\" host entry\n", host);

	/* Map transport protocol name to protocol number */
	if ( (ppe = getprotobyname(transport)) == 0)
	    errexit("can't get \"%s\" protocol entry\n", transport);

	/* Use protocol to choose a socket type */
	if (strcmp(transport, "udp") == 0)
	    type = SOCK_DGRAM;
	else
	    type = SOCK_STREAM;

	 /* Allocate a socket */
	s = socket(PF_INET, type, ppe->p_proto);
	if (s < 0)
	    errexit("can't create socket: %s\n", strerror(errno));


	/* Connect the socket */
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	  	errexit("can't connect to %s.%s: %s\n", host, service,
			strerror(errno));

	return s;
}
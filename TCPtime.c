/* TCPtime.c - TCP client for TIME service that prints the resulting time */

#include <arpa/inet.h> // ntohl
#include<stdio.h> // fprint
#include <unistd.h> // write, read
#include <string.h> // strlen
#include <time.h> // ctime
#include <stdlib.h> // exit

#define MSG 						"what time is it?\n"
#define UNIXEPOCH 					2208988800 	/* TIME protocol uses, midnight January 1, 1900 as its epoch(this # is the number of seconds between the UNIX epoch and internet epoch*/
#define LINELEN						128

extern int connectTCP(const char *host, const char *service);

void TCPtime(const char *host, const char *service)
{

	int s, n; // create variable for socket descriptor and read count
	time_t now; /* 32-bit integer to hold time (in seconds since the epoch date) */

	/* Establishes connection with server through TCP. */
	/* Give host ip address, and service that we want(TIME service) */
	/* Returns a connected connection and socket descriptor */
	/* Postive integer indicates successful connection. */
	s = connectTCP(host, service);

	if(s<0)
	{
	    printf("No service.");
	}


	// (void) write(s, MSG, strlen(MSG)); // need if using UDP to send a request (not for TCP)

	// Read the time
	// Because we are using TCP, we don't need to send a request, and the server will send a reply
	// Need a while loop to read the message
	while( (n = read(s, (char *)&now, sizeof(now))) > 0) // n is the bits read
	{
		now = ntohl((u_long)now);  // use network to host api to convert the 32-bit value from network standard byte order into the local host byte order

		/* UNIX assumes an epoch date of January 1, 1970 */
		/* for conversion, from TIME epoch to UNIX epoch, subtract # of seconds b/w January 1, 1900 & January 1,1970 */
		now = now - UNIXEPOCH; // time stored in "now" variable should be converted to machine's local representation(convert UCT to UNIX epoch)
 		printf("\n%s", ctime(&now)); // ctime returns string representation
		exit(0);
	}

	exit(0);
}
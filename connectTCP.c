/* connectTCP.c - procedure that connects to a specified TCP service on a specified host */
/* from textbook page: 61 */

extern int connectsock(const char *host, const char *service, const char *transport);

/*
* Arguments:
* host - name of host to which connection is desired
* service - service associated with the desired port
*/

int connectTCP(const char *host, const char *service )
{
	return connectsock(host, service, "tcp"); // returns the socket descriptor 
}
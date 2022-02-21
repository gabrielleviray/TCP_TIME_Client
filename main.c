/* main.c - TCP client for TIME service that prints the resulting time */

#include "procedures.h"
#include <stdio.h>
#include <stdlib.h> // exit


int main(int argc, char *argv[])
{
	char *host = "localhost";	/* default host if none is given*/
	char *service = "time";		/* default service port */

	/* pass arguments to the vector - book page 66 */
	switch (argc)
	{
		case 1:
			host = "localhost";

			break;
		case 3:
			host = argv[2];

		break;
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr, "usage: TCPtime [host [port]]\n");
			exit(1);
	}

	/* Call TCPtime procedure */
	TCPtime(host, service);

	exit(0);
}
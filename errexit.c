/* errexit.c - when there's an error, print error message, and exit */
// Page 65 of Internetworking with TCP/IP_Vol3 Textbook

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int errexit(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}
/* procedures.h - header file for all function declarations */

int errexit(const char *format, ...);
int connectsock(const char *host, const char *service, const char *transport);
int connectTCP(const char *host, const char *service);
int TCPtime(const char *host, const char *service);
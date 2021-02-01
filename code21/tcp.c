#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static int assert(const char *name, int retval)
{
   if (retval == -1)
   {
      perror(name);
      exit(EXIT_FAILURE);
   }
   return retval;
}

int tcpListen(struct sockaddr_in *addr, uint16_t port)
{
   int opt = 1;   
   int fd = assert("socket", socket(AF_INET, SOCK_STREAM, 0));
   assert("setsockopt", setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                                   (char *)&opt, sizeof opt));
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = INADDR_ANY;
   addr->sin_port = htons(port);
   assert("bind", bind(fd, (struct sockaddr *)addr, sizeof *addr));
   assert("listen", listen(fd, 3));
   printf("Listening to port %u.\n", (unsigned int)port);
   return fd;
}

int tcpAccept(struct sockaddr_in *addr, int listener)
{
   socklen_t len = sizeof *addr;
   return assert("accept", accept(listener, (struct sockaddr *)addr, &len));
}

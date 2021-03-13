#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include "object.h"
#include "print.h"

static int assert(const char *name, int retval)
{
   if (retval == -1) perror(name);
   return retval;
}

static struct sockaddr *setPort(struct sockaddr_in *addr, uint16_t port)
{
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = INADDR_ANY;
   addr->sin_port = htons(port);
   return (struct sockaddr *)addr;
}

int tcpListen(struct sockaddr_in *addr, uint16_t port)
{
   int fd = assert("socket", socket(AF_INET, SOCK_STREAM, 0));
   if (fd != -1)
   {
      int opt = 1;
      if (-1 != assert("setsockopt", setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                                                (char *)&opt, sizeof opt)) &&
          -1 != assert("bind", bind(fd, setPort(addr, port), sizeof *addr)) &&
          -1 != assert("listen", listen(fd, 3)))
      {
         printConsole("Listening to port %u.\n", (unsigned int)port);
      }
      else
      {
         close(fd);
         fd = -1;
      }
   }
   return fd;
}

void tcpClose(int fd, uint16_t port)
{
   close(fd);
   printConsole("No longer listening to port %u.\n", (unsigned int)port);
}

int tcpSelect(int nfds, fd_set *readfds)
{
   return assert("select", select(nfds, readfds, NULL, NULL, NULL));
}

int tcpAccept(struct sockaddr_in *addr, int listener)
{
   socklen_t len = sizeof *addr;
   return assert("accept", accept(listener, (struct sockaddr *)addr, &len));
}

void tcpSend(int fd, const char *data, int len)
{
   int written;
   while (len > 0 && ((written = write(fd, data, len)) >= 0 || errno == EINTR))
   {
      if (written > 0) data += written, len -= written;
   }
}

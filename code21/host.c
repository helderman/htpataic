#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include "print.h"
#include "object.h"
#include "outbuf.h"
#include "telnet.h"
#include "client.h"
#include "tcp.h"

#define PORT  8888

void host(bool (*action)(char *, int))
{
   struct sockaddr_in address;
   int listener = tcpListen(&address, PORT);
   clientInit();

   for (;;)
   {
      fd_set fds;
      CLIENT *client;
      int i;
      int fd = listener;
      FD_ZERO(&fds);
      FD_SET(listener, &fds);
      for (i = 0; (client = clientGet(i)) != NULL; i++)
      {
         if (client->fd != -1) FD_SET(client->fd, &fds);
         if (client->fd > fd) fd = client->fd;
      }
      select(fd + 1, &fds, NULL, NULL, NULL);

      if (FD_ISSET(listener, &fds))
      {
         fd = tcpAccept(&address, listener);
         printf("Socket %d connected.\n", fd);
         outbufClear();
         telnetWelcome("Welcome to Little Cave Adventure.\n");
         client = clientGetFree();
         if (client != NULL)
         {
            client->fd = fd;
            client->obj = nobody;
            telnetInit(&client->inbuf);
            telnetAppendPrompt(&client->inbuf);
         }
         else
         {
            outbufString("All sockets occupied, please try again later.\n");
         }
         outbufFlush(fd);
      }
      for (i = 0; (client = clientGet(i)) != NULL; i++)
      {
         if (FD_ISSET(client->fd, &fds))
         {
            static char buffer[1024];
            int len = read(client->fd, buffer, sizeof buffer);
            if (len > 0)
            {
               player = client->obj;
               printSetCurrent(client->fd);
               telnetParse(client->fd, &client->inbuf, action, buffer, len);
               if (client->obj == nobody) client->obj = player;
            }
            else if (len == 0)   
            {
               printf("Socket %d disconnected.\n", client->fd);
               close(client->fd);
               client->fd = -1;
            }
         }
      }
   }
}

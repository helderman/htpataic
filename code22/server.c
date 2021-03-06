#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include "break.h"
#include "object.h"
#include "print.h"
#include "outbuf.h"
#include "telnet.h"
#include "client.h"
#include "tcp.h"

#define PORT  18811

static void disconnect(CLIENT *client)
{
   if (client->fd != -1)
   {
      close(client->fd);
      printConsole("Socket %d disconnected.\n", client->fd);
      client->fd = -1;
   }
}

void server(bool (*action)(char *, int))
{
   struct sockaddr_in address;
   int listener = tcpListen(&address, PORT);
   int i;
   CLIENT *client;
   clientInit();

   for (breakInit(); breakTest(); )
   {
      fd_set fds;
      int fd = listener;
      FD_ZERO(&fds);
      FD_SET(listener, &fds);
      for (i = 0; (client = clientGet(i)) != NULL; i++)
      {
         if (client->fd != -1) FD_SET(client->fd, &fds);
         if (client->fd > fd) fd = client->fd;
      }
      if (tcpSelect(fd + 1, &fds) == -1) break;

      if (FD_ISSET(listener, &fds))
      {
         fd = tcpAccept(&address, listener);
         if (fd == -1) break;
         printConsole("Socket %d connected.\n", fd);
         outbufClear();
         telnetConfigure();
         outbufFormat("Welcome to Little Cave Adventure.\n");
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
            outbufFormat("All sockets occupied, please try again later.\n");
         }
         outbufFlush(fd);
      }
      for (i = 0; breakTest() && (client = clientGet(i)) != NULL; i++)
      {
         if (FD_ISSET(client->fd, &fds))
         {
            static char buffer[1024];
            int len = read(client->fd, buffer, sizeof buffer);
            if (len > 0)
            {
               player = client->obj;
               printSetCurrent(client->fd);
               telnetParse(&client->inbuf, client->fd, action, buffer, len);
               if (player != client->obj)
               {
                  printConsole("Socket %d is %s.\n", fd, player->description);
                  client->obj = player;
               }
            }
            else if (len == 0)   
            {
               disconnect(client);
            }
         }
      }
   }
   printConsole("Interrupted by signal %d.\n", breakSignalNumber());
   for (i = 0; (client = clientGet(i)) != NULL; i++) disconnect(client);
   tcpClose(listener, PORT);
}

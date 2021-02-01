#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "outbuf.h"
#include "telnet.h"
#include "client.h"

static int currentSocket = -1;

static void printToAll(const char *observe, const char *format, va_list ap)
{
   if (currentSocket == -1)
   {
      vprintf(format, ap);
   }
   else
   {
      outbufClear();
      outbufFormat(format, ap);
      outbufFlush(currentSocket);
      if (observe != NULL && outbufStartsWith("You ", 4))
      {
         CLIENT *client;
         int i;
         outbufInsertString(3, player->description);
         outbufInsertString(3, observe);
         telnetInsertHome();
         for (i = 0; (client = clientGet(i)) != NULL; i++)
         {
            if (client->fd != -1 && client->fd != currentSocket &&
                client->obj->location == player->location)
            {
               telnetInsertSpaces(&client->inbuf);
               telnetAppendPrompt(&client->inbuf);
               outbufFlush(client->fd);
               telnetDeletePrompt(&client->inbuf);
               telnetDeleteSpaces(&client->inbuf);
            }
         }
      }
   }
}

void printSetCurrent(int fd)
{
   currentSocket = fd;
}

void printPrivate(const char *format, ...)
{
   va_list ap;
   va_start(ap, format);
   printToAll(NULL, format, ap);
   va_end(ap);
}

void printSee(const char *format, ...)
{
   va_list ap;
   va_start(ap, format);
   printToAll(" see ", format, ap);
   va_end(ap);
}

void printHear(const char *format, ...)
{
   va_list ap;
   va_start(ap, format);
   printToAll(" hear ", format, ap);
   va_end(ap);
}

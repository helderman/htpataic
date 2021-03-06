#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "object.h"
#include "outbuf.h"
#include "telnet.h"
#include "client.h"

#define VA(print)  va_list ap; va_start(ap, format); print; va_end(ap)

static int currentSocket = STDOUT_FILENO;

static bool filter(OBJECT *obj, OBJECT *obj1, OBJECT *obj2)
{
   return obj2 == NULL ? obj == obj1 : obj != obj1 && obj != obj2;
}

static void printDemux(OBJECT *obj1, OBJECT *obj2)
{
   if (currentSocket == STDOUT_FILENO || player == nobody)
   {
      if (filter(player, obj1, obj2)) outbufFlush(currentSocket);
   }
   else
   {
      CLIENT *client;
      int i;
      for (i = 0; (client = clientGet(i)) != NULL; i++)
      {
         if (client->fd != -1 && client->obj->location == player->location &&
             filter(client->obj, obj1, obj2))
         {
            if (client->fd == currentSocket)
            {
               outbufFlush(client->fd);
            }
            else
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

static void printObserve(OBJECT *obj1, OBJECT *obj2, const char *sense,
                         const char *format, va_list ap)
{
   outbufClear();
   outbufFormatVar(format, ap);
   if (obj1 != obj2)
   {
      printDemux(obj1, NULL);
   }
   if (sense != NULL)
   {
      outbufInsertString(3, obj1->description);
      outbufInsertString(3, sense);
      printDemux(obj2, obj1);
   }
}

static void printFd(int fd, const char *format, va_list ap)
{
   outbufClear();
   outbufFormatVar(format, ap);
   outbufFlush(fd);
}

void printSetCurrent(int fd)
{
   currentSocket = fd;
}

void printConsole(const char *format, ...)
{
   VA(printFd(STDOUT_FILENO, format, ap));
}

void printPrivate(const char *format, ...)
{
   VA(printFd(currentSocket, format, ap));
}

void printSee(const char *format, ...)
{
   VA(printObserve(player, NULL, " see ", format, ap));
}

void printAny(OBJECT *obj1, OBJECT *obj2, const char *sense,
              const char *format, ...)
{
   VA(printObserve(obj1, obj2, sense, format, ap));
}

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "outbuf.h"
#include "telnet.h"

static const char prompt[] = "--> ";

void telnetInit(INBUF *inbuf)
{
   inbuf->subnegotiation = false;
   inbuf->index = 0;
}

void telnetWelcome(const char *format, ...)
{
   static const char config[] = {
      '\xFF', '\xFD', 34, '\xFF', '\xFA', 34, 1, 0, '\xFF', '\xF0',
      '\xFF', '\xFB', 1
   };
   va_list ap;
   va_start(ap, format);
   outbufBytes(config, sizeof config);
   outbufFormat(format, ap);
   va_end(ap);
}

void telnetInsertHome(void)
{
   outbufInsertString(0, "\r\r");
}

void telnetInsertSpaces(INBUF *inbuf)
{
   outbufInsertSpaces(1, inbuf->data, inbuf->index);
   outbufInsertSpaces(1, prompt, sizeof prompt - 1);
}

void telnetDeleteSpaces(INBUF *inbuf)
{
   outbufMove(inbuf->index + sizeof prompt, 1);
}

void telnetAppendPrompt(INBUF *inbuf)
{
   outbufBytes(prompt, sizeof prompt - 1);
   outbufBytes(inbuf->data, inbuf->index);
}

void telnetDeletePrompt(INBUF *inbuf)
{
   outbufRewind(inbuf->index + sizeof prompt - 1);
}

void telnetParse(int fd, INBUF *inbuf, bool (*action)(char *, int),
                 const char *data, int length)
{
   int i;
   outbufClear();
   for (i = 0; i < length; i++)
   {
      int c = data[i];
      if (c == '\xFF')
      {
         switch (data[++i])
         {
            case '\xF0':
               inbuf->subnegotiation = false;
               break;
            case '\xFA':
               inbuf->subnegotiation = true;
               break;
            case '\xFB': case '\xFC': case '\xFD': case '\xFE':
               i++;
               break;
         }
      }
      else if (inbuf->subnegotiation)
      {
      }
      else if (c == '\r')
      {
         outbufByte('\r');
         outbufByte('\n');
         outbufFlush(fd);
         inbuf->data[inbuf->index] = '\0';
         (*action)(inbuf->data, sizeof inbuf->data);
         inbuf->index = 0;
         outbufClear();
         outbufBytes(prompt, sizeof prompt - 1);
      }
      else if (c == '\b' || c == '\x7F')
      {
         if (inbuf->index > 0)
	 {
            outbufByte('\b');
            outbufAsSpace(inbuf->data[--inbuf->index]);
            outbufByte('\b');
	 }
      }
      else if (c >= ' ' && c < '\x7F')
      {
         if (inbuf->index < sizeof inbuf->data - 1)
         {
            outbufByte(c);
            inbuf->data[inbuf->index++] = c;
         }
      }
   }
   outbufFlush(fd);
}

#include <stdbool.h>
#include <stdio.h>
#include "outbuf.h"
#include "telnet.h"

static const char prompt[] = "--> ";

void telnetInit(INBUF *inbuf)
{
   inbuf->iac = false;
   inbuf->negotiate = 0;
   inbuf->index = 0;
}

void telnetConfigure(void)
{
   static const char config[] = {
      '\xFF', '\xFD', 34, '\xFF', '\xFA', 34, 1, 0, '\xFF', '\xF0',
      '\xFF', '\xFB', 1
   };
   outbufBytes(config, sizeof config);
}

void telnetInsertSpaces(INBUF *inbuf)
{
   outbufInsertString(0, "\r\r");
   outbufInsertSpaces(1, inbuf->data, inbuf->index);
   outbufInsertSpaces(1, prompt, sizeof prompt - 1);
}

void telnetDeleteSpaces(INBUF *inbuf)
{
   outbufMove(inbuf->index + sizeof prompt + 1, 0);
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

void telnetParse(INBUF *inbuf, int fd, bool (*action)(char *, int),
                 const char *data, int length)
{
   int i;
   outbufClear();
   for (i = 0; i < length; i++)
   {
      int c = data[i];
      if (c == '\xFF' || inbuf->iac)
      {
         if (c == '\xF0' || inbuf->negotiate != '\xFA') inbuf->negotiate = c;
         inbuf->iac = !inbuf->iac;
      }
      else if (inbuf->negotiate >= '\xFA' && inbuf->negotiate <= '\xFE')
      {
         if (inbuf->negotiate != '\xFA') inbuf->negotiate = 0;
      }
      else if (c == '\r')
      {
         outbufFormat("\n");
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

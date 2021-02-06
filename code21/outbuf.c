#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include "tcp.h"

#define MAX_LEN  4095

static int outbufLen;
static char outbufData[MAX_LEN + 1];

static int asSpace(int c)
{
   return isspace(c) ? c : ' ';
}

void outbufClear(void)
{
   outbufLen = 0;
}

void outbufRewind(int len)
{
   outbufLen -= len;
}

void outbufByte(char c)
{
   if (outbufLen < MAX_LEN) outbufData[outbufLen++] = c;
}

void outbufBytes(const char *data, int length)
{
   for (; length > 0; length--) outbufByte(*data++);
}

void outbufAsSpace(char c)
{
   outbufByte(asSpace(c));
}

void outbufFormatVar(const char *format, va_list ap)
{
   char *ptr = outbufData + outbufLen;
   outbufLen += vsnprintf(ptr, sizeof outbufData - outbufLen, format, ap);
   if (outbufLen > MAX_LEN) outbufLen = MAX_LEN;
   while (outbufLen < MAX_LEN && (ptr = strchr(ptr, '\n')) != NULL)
   {
      memmove(ptr + 1, ptr, outbufData + ++outbufLen - ptr);
      *ptr = '\r';
      ptr += 2;
   }
}

void outbufFormat(const char *format, ...)
{
   va_list ap;
   va_start(ap, format);
   outbufFormatVar(format, ap);
   va_end(ap);
}

bool outbufStartsWith(const char *prefix, int len)
{
   return outbufLen >= len && strncmp(outbufData, prefix, len) == 0;
}

bool outbufMove(int from, int to)
{
   outbufLen += to - from;
   if (outbufLen > MAX_LEN) outbufLen = MAX_LEN;
   if (to < outbufLen)
   {
      memmove(outbufData + to, outbufData + from, outbufLen - to);
   }
   return to <= outbufLen;
}

void outbufInsertString(int pos, const char *string)
{
   int len = strlen(string);
   if (outbufMove(pos, pos + len)) strncpy(outbufData + pos, string, len);
}

void outbufInsertSpaces(int pos, const char *data, int len)
{
   if (outbufMove(pos, pos + len))
   {
      int i;
      for (i = pos; i < pos + len; i++) outbufData[i] = asSpace(data[i]);
   }
}

void outbufFlush(int fd)
{
   tcpSend(fd, outbufData, outbufLen);
}

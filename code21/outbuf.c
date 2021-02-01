#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SIZE  4096

static int outbufLen;
static char outbufData[BUF_SIZE + 1];

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
   if (outbufLen < BUF_SIZE) outbufData[outbufLen++] = c;
}

void outbufBytes(const char *data, int length)
{
   for (; length > 0; length--) outbufByte(*data++);
}

void outbufAsSpace(char c)
{
   outbufByte(asSpace(c));
}

void outbufString(const char *string)
{
   outbufBytes(string, strlen(string));
}

void outbufFormat(const char *format, va_list ap)
{
   char *ptr = outbufData + outbufLen;
   outbufLen += vsnprintf(ptr, sizeof outbufData - outbufLen, format, ap);
   if (outbufLen > BUF_SIZE) outbufLen = BUF_SIZE;
   while (outbufLen < BUF_SIZE && (ptr = strchr(ptr, '\n')) != NULL)
   {
      memmove(ptr + 1, ptr, outbufData + ++outbufLen - ptr);
      *ptr = '\r';
      ptr += 2;
   }
}

bool outbufStartsWith(const char *prefix, int len)
{
   return outbufLen >= len && strncmp(outbufData, prefix, len) == 0;
}

bool outbufMove(int from, int to)
{
   outbufLen += to - from;
   if (outbufLen > BUF_SIZE) outbufLen = BUF_SIZE;
   if (to < outbufLen)
   {
      memmove(outbufData + to, outbufData + from, outbufLen - to);
   }
   return to <= outbufLen;
}

void outbufInsertBytes(int pos, const char *data, int len)
{
   if (outbufMove(pos, pos + len)) strncpy(outbufData + pos, data, len);
}

void outbufInsertString(int pos, const char *string)
{
   outbufInsertBytes(pos, string, strlen(string));
}

void outbufInsertSpaces(int pos, const char *data, int len)
{
   if (outbufMove(pos, pos + len))
   {
      int i;
      for (i = pos; i < pos + len; i++) outbufData[i] = asSpace(data[i]);
   }
}

void outbufFlush(int socket)
{
   if (outbufLen > 0) send(socket, outbufData, outbufLen, 0);
}

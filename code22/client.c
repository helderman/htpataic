#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "telnet.h"
#include "client.h"

#define MAX_CLIENTS  30

static CLIENT clients[MAX_CLIENTS];

void clientInit(void)
{
   int i;
   for (i = 0; i < MAX_CLIENTS; i++) clients[i].fd = -1;
}

CLIENT *clientGet(int i)
{
   return i < MAX_CLIENTS ? clients + i : NULL;
}

CLIENT *clientGetFree(void)
{
   CLIENT *client;
   int i;
   for (i = 0; (client = clientGet(i)) != NULL && client->fd != -1; i++);
   return client;
}

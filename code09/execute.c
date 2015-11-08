#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "move.h"

void executeGet(const char *noun)
{
   moveObject(noun, player->location, player);
}

void executeDrop(const char *noun)
{
   moveObject(noun, player, player->location);
}

void executeAsk(const char *noun)
{
   moveObject(noun, actorHere(), player);
}

void executeGive(const char *noun)
{
   moveObject(noun, player, actorHere());
}

void executeInventory(void)
{
   if (listObjectsAtLocation(player) == 0)
   {
      printf("You are empty-handed.\n");
   }
}

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "move.h"

void executeOpen(const char *noun)
{
   OBJECT *obj = matchingObject(noun);
   if (objectWithinReach("open", obj, noun))
   {
      printf("%s", (*obj->open)());
   }
}

void executeClose(const char *noun)
{
   OBJECT *obj = matchingObject(noun);
   if (objectWithinReach("close", obj, noun))
   {
      printf("%s", (*obj->close)());
   }
}

void executeLock(const char *noun)
{
   OBJECT *obj = matchingObject(noun);
   if (objectWithinReach("lock", obj, noun))
   {
      printf("%s", (*obj->lock)());
   }
}

void executeUnlock(const char *noun)
{
   OBJECT *obj = matchingObject(noun);
   if (objectWithinReach("unlock", obj, noun))
   {
      printf("%s", (*obj->unlock)());
   }
}

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

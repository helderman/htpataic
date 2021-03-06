#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "noun.h"
#include "move.h"

int executeGet(void)
{
   OBJECT *obj = getVisible("what you want to get", params[0]);
   switch (getDistance(player, obj))
   {
   case distSelf:
      printf("You should not be doing that to yourself.\n");
      return 1;
   case distHeld:
      printf("You already have %s.\n", obj->description);
      return 0;
   case distOverthere:
      printf("Too far away, move closer please.\n");
      return 0;
   case distUnknownObject:
      // already handled by getVisible
      return 0;
   default:
      if (obj->location != NULL && obj->location->health > 0)
      {
         printf("You should ask %s nicely.\n", obj->location->description);
         return 1;
      }
      else
      {
         return moveObject(obj, player);
      }
   }
}

int executeDrop(void)
{
   return moveObject(getPossession(player, "drop", params[0]), player->location);
}

int executeAsk(void)
{
   return moveObject(getPossession(actorHere(), "ask", params[0]), player);
}

int executeGive(void)
{
   return moveObject(getPossession(player, "give", params[0]), actorHere());
}

int executeInventory(void)
{
   if (listObjectsAtLocation(player) == 0)
   {
      printf("You are empty-handed.\n");
   }
   return 1;
}

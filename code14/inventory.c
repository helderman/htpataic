#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "noun.h"
#include "move.h"
#include "reach.h"

bool executeGet(void)
{
   OBJECT *obj = getVisible("what you want to get", params[0]);
   switch (getDistance(player, obj))
   {
   case distSelf:
      printf("You should not be doing that to %s.\n", obj->description);
      break;
   case distHeld:
      printf("You already have %s.\n", obj->description);
      break;
   case distOverthere:
      printf("Too far away, move closer please.\n");
      break;
   case distUnknownObject:
      // already handled by getVisible
      break;
   default:
      if (obj->location != NULL && obj->location->health > 0)
      {
         printf("You should ask %s nicely.\n", obj->location->description);
      }
      else
      {
         moveObject(obj, player);
      }
   }
   return true;
}

bool executeDrop(void)
{
   moveObject(getPossession(player, "drop", params[0]), player->location);
   return true;
}

bool executeAsk(void)
{
   moveObject(getPossession(actorHere(), "ask", params[0]), player);
   return true;
}

bool executeGive(void)
{
   moveObject(getPossession(player, "give", params[0]), actorHere());
   return true;
}

bool executeGetFrom(void)
{
   // TODO: need a getVisible that does not report ambiguous noun
   // TODO: report if actor
   if (getVisible("what you want to get", params[0]) != NULL)
   {
      OBJECT *from = reachableObject("where to get that from", params[1]);
      moveObject(getPossession(from, "get", params[0]), player);
   }
   return true;
}

bool executePutIn(void)
{
   // TODO: report if actor
   OBJECT *obj = getPossession(player, "put", params[0]);
   if (obj != NULL)
   {
      OBJECT *to = reachableObject("where to put that in", params[1]);
      moveObject(obj, to);
   }
   return true;
}

bool executeAskFrom(void)
{
   // TODO: need a getVisible that does not report ambiguous noun
   // TODO: report if not actor
   if (getVisible("what you want to ask", params[0]) != NULL)
   {
      OBJECT *from = reachableObject("who to ask that", params[1]);
      moveObject(getPossession(from, "ask", params[0]), player);
   }
   return true;
}

bool executeGiveTo(void)
{
   // TODO: report if not actor (not really error; especially when dead actor)
   OBJECT *obj = getPossession(player, "give", params[0]);
   if (obj != NULL)
   {
      OBJECT *to = reachableObject("who to give that to", params[1]);
      moveObject(obj, to);
   }
   return true;
}

bool executeInventory(void)
{
   if (listObjectsAtLocation(player) == 0)
   {
      printf("You are empty-handed.\n");
   }
   return true;
}

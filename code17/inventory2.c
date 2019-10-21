#include <stdio.h>
#include "object.h"
#include "match.h"
#include "noun.h"
#include "move.h"
#include "reach.h"

bool executeGetFrom(void)
{
   // TODO: report if actor
   OBJECT *from = reachableObject("where to get that from", params[1]);
   if (from != NULL && getVisible("what you want to get", params[0]) != NULL)
   {
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
      if (to != NULL)
      {
         moveObject(obj, to);
      }
   }
   return true;
}

bool executeAskFrom(void)
{
   // TODO: report if not actor
   OBJECT *from = reachableObject("who to ask that", params[1]);
   if (from != NULL && getVisible("what you want to ask", params[0]) != NULL)
   {
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
      if (to != NULL)
      {
         moveObject(obj, to);
      }
   }
   return true;
}

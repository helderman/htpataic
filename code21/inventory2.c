#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "match.h"
#include "noun.h"
#include "move.h"
#include "reach.h"

int executeGetFrom(void)
{
   OBJECT *from = reachableObject("where to get that from", params[1]);
   if (from != NULL && getVisible("what you want to get", params[0]) != NULL)
   {
      if (from->health > 0)
      {
         printf("You should ask %s nicely.\n", from->description);
         return 1;
      }
      else
      {
         return moveObject(getPossession(from, "get", params[0]), player);
      }
   }
   return 0;
}

int executePutIn(void)
{
   OBJECT *obj = getPossession(player, "put", params[0]);
   if (obj != NULL)
   {
      OBJECT *to = reachableObject("where to put that in", params[1]);
      if (to != NULL)
      {
         if (to->health > 0)
         {
            printf("You should offer that nicely to %s.\n", to->description);
            return 1;
         }
         else
         {
            return moveObject(obj, to);
         }
      }
   }
   return 0;
}

int executeAskFrom(void)
{
   OBJECT *from = reachableObject("who to ask that", params[1]);
   if (from != NULL)
   {
      if (from->health > 0)
      {
         if (getVisible("what you want to ask", params[0]) != NULL)
         {
            return moveObject(getPossession(from, "ask", params[0]), player);
         }
      }
      else
      {
         printf("There is no response from %s.\n", from->description);
         return 1;
      }
   }
   return 0;
}

int executeGiveTo(void)
{
   OBJECT *obj = getPossession(player, "give", params[0]);
   if (obj != NULL)
   {
      OBJECT *to = reachableObject("who to give that to", params[1]);
      if (to != NULL)
      {
         if (to->health > 0)
         {
            return moveObject(obj, to);
         }
         else
         {
            printf("No eagerness is shown by %s.\n", to->description);
            return 1;
         }
      }
   }
   return 0;
}

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "noun.h"

OBJECT *reachableObject(const char *intention, const char *noun)
{
   OBJECT *obj = getVisible(intention, noun);
   switch (getDistance(player, obj))
   {
   case distSelf:
      printf("You should not be doing that to %s.\n", obj->description);
      break;
   case distHeldContained:
   case distHereContained:
      printf("You would have to get it from %s first.\n",
             obj->location->description);
      break;
   case distOverthere:
      printf("Too far away, move closer please.\n");
      break;
   case distNotHere:
   case distUnknownObject:
      // already handled by getVisible
      break;
   default:
      return obj;
   }
   return NULL;
}

void moveObject(OBJECT *obj, OBJECT *to)
{
   if (obj == NULL)
   {
      // already handled by getVisible or getPossession
   }
   else if (to == NULL)
   {
      printf("There is nobody here to give that to.\n");
   }
   else if (obj->weight > to->capacity)
   {
      printf("That is way too heavy.\n");
   }
   else if (obj->weight + weightOfContents(to) > to->capacity)
   {
      printf("That would become too heavy.\n");
   }
   else
   {
      if (to == player->location)
      {
         printf("You drop %s.\n", obj->description);
      }
      else if (to != player)
      {
         printf(to->health > 0 ? "You give %s to %s.\n"
                               : "You put %s in %s.\n",
                obj->description, to->description);
      }
      else if (obj->location == player->location)
      {
         printf("You pick up %s.\n", obj->description);
      }
      else
      {
         printf("You get %s from %s.\n", obj->description,
                                         obj->location->description);
      }
      obj->location = to;
   }
}

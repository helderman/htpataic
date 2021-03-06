#include <stdbool.h>
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
      printf("You should not be doing that to yourself.\n");
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

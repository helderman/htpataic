#include <stdbool.h>
#include <stdio.h>
#include "print.h"
#include "object.h"
#include "misc.h"
#include "noun.h"

OBJECT *reachableObject(const char *intention, const char *noun)
{
   OBJECT *obj = getVisible(intention, noun);
   switch (getDistance(player, obj))
   {
   case distSelf:
      printPrivate("You should not be doing that to %s.\n", obj->description);
      break;
   case distHeldContained:
   case distHereContained:
      printPrivate("You would have to get it from %s first.\n",
                   obj->location->description);
      break;
   case distOverthere:
      printPrivate("Too far away, move closer please.\n");
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
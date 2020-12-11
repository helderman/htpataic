#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"

bool isHolding(OBJECT *container, OBJECT *obj)
{
   return obj != NULL && obj->location == container;
}

OBJECT *getPassage(OBJECT *from, OBJECT *to)
{
   if (from != NULL && to != NULL)
   {
      OBJECT *obj;
      for (obj = objs; obj < endOfObjs; obj++)
      {
         if (isHolding(from, obj) && obj->destination == to)
         {
            return obj;
         }
      }
   }
   return NULL;
}

DISTANCE getDistance(OBJECT *from, OBJECT *to)
{
   return to == NULL                               ? distUnknownObject :
          to == from                               ? distSelf :
          isHolding(from, to)                      ? distHeld :
          isHolding(to, from)                      ? distLocation :
          isHolding(from->location, to)            ? distHere :
          isHolding(from, to->location)            ? distHeldContained :
          isHolding(from->location, to->location)  ? distHereContained :
          getPassage(from->location, to) != NULL   ? distOverthere :
                                                     distNotHere;
}

OBJECT *actorHere(void)
{
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (isHolding(player->location, obj) && obj == guard)
      {
         return obj;
      }
   }
   return NULL;
}

int listObjectsAtLocation(OBJECT *location)
{
   int count = 0;
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (obj != player && isHolding(location, obj))
      {
         if (count++ == 0)
         {
            printf("You see:\n");
         }
         printf("%s\n", obj->description);
      }
   }
   return count;
}

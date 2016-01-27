#include <stdio.h>
#include "object.h"
#include "misc.h"

OBJECT *getPassage(OBJECT *from, OBJECT *to)
{
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (obj->location == from && obj->destination == to)
      {
         return obj;
      }
   }
   return NULL;
}

DISTANCE getDistance(OBJECT *from, OBJECT *to)
{
   return to == NULL                               ? distUnknownObject :
          to == from                               ? distSelf :
          to->location == from                     ? distHeld :
          to == from->location                     ? distLocation :
          to->location == from->location           ? distHere :
          getPassage(from->location, to) != NULL   ? distOverthere :
          to->location == NULL                     ? distNotHere :
          to->location->location == from           ? distHeldContained :
          to->location->location == from->location ? distHereContained :
                                                     distNotHere;
}

OBJECT *actorHere(void)
{
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (getDistance(player, obj) == distHere && obj == guard)
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
      if (obj != player && obj->location == location)
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

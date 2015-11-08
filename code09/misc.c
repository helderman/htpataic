#include <stdio.h>
#include "object.h"
#include "misc.h"

OBJECT *getPassageTo(OBJECT *targetLocation)
{
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (obj->location == player->location &&
          obj->destination == targetLocation)
      {
         return obj;
      }
   }
   return NULL;
}

DISTANCE distanceTo(OBJECT *obj)
{
   return obj == NULL                                 ? distUnknownObject :
          obj == player                               ? distPlayer :
          obj->location == player                     ? distHeld :
          obj == player->location                     ? distLocation :
          obj->location == player->location           ? distHere :
          getPassageTo(obj) != NULL                   ? distOverthere :
          obj->location == NULL                       ? distNotHere :
          obj->location->location == player           ? distHeldContained :
          obj->location->location == player->location ? distHereContained :
                                                        distNotHere;
}

OBJECT *actorHere(void)
{
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (distanceTo(obj) == distHere && obj == guard)
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

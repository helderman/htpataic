#include <stdio.h>
#include "object.h"
#include "misc.h"

OBJECT *getPassageTo(OBJECT *targetLocation)
{
   OBJECT *obj;
   forEachObject(obj)
   {
      if (obj->location == player->location &&
          obj->prospect == targetLocation)
      {
         return obj;
      }
   }
   return NULL;
}

DISTANCE distanceTo(OBJECT *obj)
{
   return !validObject(obj)                           ? distUnknownObject :
          obj == player                               ? distPlayer :
          obj->location == player                     ? distHeld :
          obj == player->location                     ? distLocation :
          obj->location == player->location           ? distHere :
          getPassageTo(obj) != NULL                   ? distOverthere :
          !validObject(obj->location)                 ? distNotHere :
          obj->location->location == player           ? distHeldContained :
          obj->location->location == player->location ? distHereContained :
                                                        distNotHere;
}

OBJECT *actorHere(void)
{
   OBJECT *obj;
   forEachObject(obj)
   {
      if (distanceTo(obj) == distHere && obj->health > 0)
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
   forEachObject(obj)
   {
      if (obj != player && obj->location == location)
      {
         if (count++ == 0)
         {
            printf("%s:\n", location->contents);
         }
         printf("%s\n", obj->description);
      }
   }
   return count;
}

int weightOfContents(OBJECT *container)
{
   int sum = 0;
   OBJECT *obj;
   forEachObject(obj)
   {
      if (obj->location == container) sum += obj->weight;
   }
   return sum;
}

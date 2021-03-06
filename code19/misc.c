#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"

bool isHolding(OBJECT *container, OBJECT *obj)
{
   return validObject(obj) && obj->location == container;
}

bool isLit(OBJECT *target)
{
   OBJECT *obj;
   if (validObject(target))
   {
      if (target->light > 0)
      {
         return true;
      }
      for (obj = objs; obj < endOfObjs; obj++)
      {
         if (validObject(obj) && obj->light > 0 &&
             (isHolding(target, obj) || isHolding(target, obj->location)))
         {
            return true;
         }
      }
   }
   return false;
}

static bool isNoticeable(OBJECT *obj)
{
   return obj->location == player ||
          isLit(obj) || isLit(obj->prospect) || isLit(player->location);
}

OBJECT *getPassage(OBJECT *from, OBJECT *to)
{
   if (from != NULL && to != NULL)
   {
      OBJECT *obj;
      for (obj = objs; obj < endOfObjs; obj++)
      {
         if (isHolding(from, obj) && obj->prospect == to)
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
          !validObject(to)                         ? distNotHere :
          to == from                               ? distSelf :
          isHolding(from, to)                      ? distHeld :
          !isNoticeable(to)                        ? distNotHere :
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
      if (isHolding(player->location, obj) && obj != player &&
          isNoticeable(obj) && obj->health > 0)
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
      if (obj != player && isHolding(location, obj) && isNoticeable(obj))
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

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

OBJECT *actorHere(void)
{
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (obj->location == player->location && obj == guard)
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

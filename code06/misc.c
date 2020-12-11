#include <stdio.h>
#include "object.h"

OBJECT *getPassage(OBJECT *from, OBJECT *to)
{
   if (from != NULL && to != NULL)
   {
      OBJECT *obj;
      for (obj = objs; obj < endOfObjs; obj++)
      {
         if (obj->location == from && obj->destination == to)
         {
            return obj;
         }
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

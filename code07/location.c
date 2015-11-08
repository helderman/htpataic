#include <stdio.h>
#include <string.h>
#include "object.h"
#include "misc.h"
#include "match.h"

void executeLook(const char *noun)
{
   if (noun != NULL && strcmp(noun, "around") == 0)
   {
      printf("You are in %s.\n", player->location->description);
      listObjectsAtLocation(player->location);
   }
   else
   {
      printf("I don't understand what you want to see.\n");
   }
}

void executeGo(const char *noun)
{
   OBJECT *obj = matchingObject(noun);
   DISTANCE distance = distanceTo(obj);
   if (distance >= distUnknownObject)
   {
      printf("I don't understand where you want to go.\n");
   }
   else if (distance == distOverthere)
   {
      printf("OK.\n");
      player->location = obj;
      executeLook("around");
   }
   else if (distance == distHere && obj->destination != NULL)
   {
      printf("OK.\n");
      player->location = obj->destination;
      executeLook("around");
   }
   else if (distance < distNotHere)
   {
      printf("You can't get much closer than this.\n");
   }
   else
   {
      printf("You don't see any %s here.\n", noun);
   }
}

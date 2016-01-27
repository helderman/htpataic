#include <stdio.h>
#include <string.h>
#include "object.h"
#include "misc.h"
#include "noun.h"

void executeLook(const char *noun)
{
   if (noun != NULL && strcmp(noun, "around") == 0)
   {
      printf("You are in %s.\n", player->location->description);
      listObjectsAtLocation(player->location);
   }
   else
   {
      OBJECT *obj = getVisible("what you want to look at", noun);
      switch (getDistance(player, obj))
      {
      case distHereContained:
         printf("Hard to see, try to get it first.\n");
         break;
      case distOverthere:
         printf("Too far away, move closer please.\n");
         break;
      case distNotHere:
         printf("You don't see any %s here.\n", noun);
         break;
      case distUnknownObject:
         // already handled by getVisible
         break;
      default:
         printf("%s", obj->details);
         listObjectsAtLocation(obj);
      }
   }
}

static void movePlayer(OBJECT *passage)
{
   printf("%s", passage->textGo);
   if (passage->destination != NULL)
   {
      player->location = passage->destination;
      printf("\n");
      executeLook("around");
   }
}

void executeGo(const char *noun)
{
   OBJECT *obj = getVisible("where you want to go", noun);
   switch (getDistance(player, obj))
   {
   case distOverthere:
      movePlayer(getPassage(player->location, obj));
      break;
   case distNotHere:
      printf("You don't see any %s here.\n", noun);
      break;
   case distUnknownObject:
      // already handled by getVisible
      break;
   default:
      movePlayer(obj);
   }
}

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
      OBJECT *obj = matchingObject(noun);
      DISTANCE distance = distanceTo(obj);
      if (distance >= distUnknownObject)
      {
         printf("I don't understand what you want to see.\n");
      }
      else if (distance == distNotHere)
      {
         printf("You don't see any %s here.\n", noun);
      }
      else if (distance == distOverthere)
      {
         printf("Too far away, move closer please.\n");
      }
      else if (distance == distHereContained)
      {
         printf("Hard to see, try to get it first.\n");
      }
      else
      {
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
   OBJECT *obj = matchingObject(noun);
   DISTANCE distance = distanceTo(obj);
   if (distance >= distUnknownObject)
   {
      printf("I don't understand where you want to go.\n");
   }
   else if (distance == distOverthere)
   {
      movePlayer(getPassageTo(obj));
   }
   else if (distance == distHere)
   {
      movePlayer(obj);
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

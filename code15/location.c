#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"

bool executeLookAround(void)
{
   if (isInLight(player))
   {
      printf("You are in %s.\n", player->location->description);
   }
   else
   {
      printf("It is very dark in here.\n");
   }
   listObjectsAtLocation(player->location);
   return true;
}

bool executeLook(void)
{
   if (params->distance >= distUnknownObject)
   {
      printf("I don't understand what you want to see.\n");
   }
   else if (params->distance == distNotHere)
   {
      printf("You don't see any %s here.\n", params->tag);
   }
   else if (params->distance == distOverthere)
   {
      printf("Too far away, move closer please.\n");
   }
   else if (params->distance == distHereContained)
   {
      printf("Hard to see, try to get it first.\n");
   }
   else
   {
      printf("%s", params->object->details);
      listObjectsAtLocation(params->object);
   }
   return true;
}

static void movePlayer(OBJECT *passage)
{
   printf("%s", passage->textGo);
   if (passage->destination != NULL)
   {
      player->location = passage->destination;
      printf("\n");
      executeLookAround();
   }
}

bool executeGo(void)
{
   if (params->distance >= distUnknownObject)
   {
      printf("I don't understand where you want to go.\n");
   }
   else if (params->distance == distOverthere)
   {
      movePlayer(getPassageTo(params->object));
   }
   else if (params->distance == distHere)
   {
      movePlayer(params->object);
   }
   else if (params->distance < distNotHere)
   {
      printf("You can't get much closer than this.\n");
   }
   else
   {
      printf("You don't see any %s here.\n", params->tag);
   }
   return true;
}

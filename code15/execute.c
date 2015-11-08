#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "move.h"
#include "toggle.h"

bool executeOpen(void)
{
   if (objectWithinReach("open", params))
   {
      printf("%s", (*params->object->open)());
   }
   return true;
}

bool executeClose(void)
{
   if (objectWithinReach("close", params))
   {
      printf("%s", (*params->object->close)());
   }
   return true;
}

bool executeLock(void)
{
   if (objectWithinReach("lock", params))
   {
      printf("%s", (*params->object->lock)());
   }
   return true;
}

bool executeUnlock(void)
{
   if (objectWithinReach("unlock", params))
   {
      printf("%s", (*params->object->unlock)());
   }
   return true;
}

bool executeGet(void)
{
   return moveObject(params, player->location, player);
}

bool executeDrop(void)
{
   return moveObject(params, player, player->location);
}

bool executeAsk(void)
{
   return moveObject(params, actorHere(), player);
}

bool executeGive(void)
{
   return moveObject(params, player, actorHere());
}

bool executeGetFrom(void)
{
   return moveObject(params, params[1].object, player);
}

bool executePutIn(void)
{
   return moveObject(params, player, params[1].object);
}

bool executeAskFrom(void)
{
   return moveObject(params, params[1].object, player);
}

bool executeGiveTo(void)
{
   return moveObject(params, player, params[1].object);
}

bool executeInventory(void)
{
   if (listObjectsAtLocation(player) == 0)
   {
      printf("You are empty-handed.\n");
   }
   return true;
}

bool executeTurnOn(void)
{
   if (objectWithinReach("turn on", params))
   {
      printf("%s", params->object == lampOff ? toggleLamp() :
                   params->object == lampOn  ? "The lamp is already on.\n" :
                                               "You cannot turn that on.\n");
   }
   return true;
}

bool executeTurnOff(void)
{
   if (objectWithinReach("turn off", params))
   {
      printf("%s", params->object == lampOn  ? toggleLamp() :
                   params->object == lampOff ? "The lamp is already off.\n" :
                                               "You cannot turn that off.\n");
   }
   return true;
}

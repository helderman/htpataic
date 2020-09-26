#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "damage.h"

static OBJECT *findBestWeaponAround(OBJECT *actor, OBJECT *weapon)
{
   OBJECT *obj;
   forEachObject(obj)
   {
      if (getDistance(actor, obj) == distHere &&
          obj->impact < weapon->impact)
      {
         weapon = obj;
      }
   }
   return weapon;
}

static void actorTakingTurn(OBJECT *actor)
{
   if (actor->trust < 0)
   {
      OBJECT *weapon = getOptimalWeapon(actor);
      OBJECT *best = findBestWeaponAround(actor, weapon);
      if (weapon == best)
      {
         dealDamage(actor, getOptimalWeapon(actor), player);
      }
      else
      {
         best->location = actor;
         printf("You see %s pick up %s.\n",
                actor->description, best->description);
      }
   }
}

bool turn(int time)
{
   if (time <= 0)
   {
      return time == 0;
   }
   else
   {
      OBJECT *obj;
      forEachObject(obj)
      {
         if (getDistance(player, obj) == distHere && obj->health > 0)
         {
            actorTakingTurn(obj);
         }
      }
      return true;
   }
}

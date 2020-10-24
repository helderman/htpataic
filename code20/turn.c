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
   if (getDistance(actor, player) == distHere && actor->trust < 0)
   {
      OBJECT *weapon = getOptimalWeapon(actor);
      OBJECT *best = findBestWeaponAround(actor, weapon);
      if (weapon == best)
      {
         dealDamage(actor, weapon, player);
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
   if (time > 0)
   {
      OBJECT *obj;
      forEachObject(obj)
      {
         if (obj->health > 0) actorTakingTurn(obj);
      }
      if (player->health <= 0)
      {
         printf("You have died and gone to little heaven.\n");
         player->location = heaven;
         player->health = 100;
         forEachObject(obj)
         {
            if (obj->location == player) obj->location = field;
         }
      }
   }
   return time >= 0;
}

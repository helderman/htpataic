#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "object.h"
#include "print.h"
#include "misc.h"

static void describeAttack(OBJECT *attacker, OBJECT *victim, OBJECT *weapon)
{
   const char *weaponDescription = weapon == attacker ? "bare hands"
                                                      : weapon->description;
   printAny(attacker, victim, " see ", "You hit %s with %s.\n",
            victim->description, weaponDescription);
   printAny(victim, NULL, NULL, "You are hit by %s with %s.\n",
            attacker->description, weaponDescription);
}

static void describeDeath(OBJECT *victim)
{
   printAny(victim, NULL, " see ", "You die.\n");
}

void dealDamage(OBJECT *attacker, OBJECT *weapon, OBJECT *victim)
{
   int damage = (rand() % 6) * weapon->impact * attacker->health / 100;
   if (damage < 0)
   {
      if (victim->health > 0)
      {
         describeAttack(attacker, victim, weapon);
         victim->health += damage;
         if (victim->health <= 0)
         {
            victim->health = 0;
            describeDeath(victim);
         }
         if (attacker == player)
         {
            victim->trust--;
         }
      }
      else if (attacker == player)
      {
         printPrivate("That will have little effect; %s is already dead.\n",
                      victim->description);
      }
   }
   else if (attacker == player)
   {
      printf("You try to hit %s with %s, but you miss.\n",
             victim->description,
             weapon == attacker ? "bare hands" : weapon->description);
   }
}

OBJECT *getOptimalWeapon(OBJECT *attacker)
{
   OBJECT *obj, *weapon = attacker;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (isHolding(attacker, obj) && obj->impact < weapon->impact)
      {
         weapon = obj;
      }
   }
   return weapon;
}

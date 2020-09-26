#include <stdlib.h>
#include <stdio.h>
#include "object.h"

static void describeAttack(OBJECT *attacker, OBJECT *victim,
                           const char *weaponDescription)
{
   if (attacker == player)
   {
      printf("You hit %s with %s.\n", victim->description, weaponDescription);
   }
   else if (victim == player)
   {
      printf("You are hit by %s, with %s.\n",
             attacker->description, weaponDescription);
   }
   else
   {
      printf("You see %s being hit by %s, with %s.\n",
             victim->description, attacker->description, weaponDescription);
   }
}

static void describeDeath(OBJECT *attacker, OBJECT *victim)
{
   if (attacker == player)
   {
      printf("You have slain %s.\n", victim->description);
   }
   else if (victim == player)
   {
      printf("You have been slain by %s.\n", attacker->description);
   }
   else
   {
      printf("You see %s being slain by %s.\n",
             victim->description, attacker->description);
   }
}

static void describeAlreadyDead(OBJECT *victim)
{
   if (victim == player)
   {
      printf("It has little effect, since you were already dead.\n");
   }
   else
   {
      printf("It has little effect, since %s was already dead.\n",
             victim->description);
   }
}

void dealDamage(OBJECT *attacker, OBJECT *weapon, OBJECT *victim)
{
   const char *weaponDescription = weapon == attacker ? "bare hands"
                                                      : weapon->description;
   int damage = (rand() % 6) * weapon->impact * attacker->health / 100;
   if (damage < 0)
   {
      describeAttack(attacker, victim, weaponDescription);
      if (victim->health <= 0)
      {
         describeAlreadyDead(victim);
      }
      else
      {
         victim->health += damage;
         if (victim->health <= 0)
         {
            victim->health = 0;
            describeDeath(attacker, victim);
         }
         if (attacker == player)
         {
            victim->trust--;
         }
      }
   }
   else if (attacker == player)
   {
      printf("You try to hit %s with %s, but you miss.\n",
             victim->description, weaponDescription);
   }
}

OBJECT *getOptimalWeapon(OBJECT *attacker)
{
   OBJECT *obj, *weapon = attacker;
   forEachObject(obj)
   {
      if (obj->location == attacker && obj->impact < weapon->impact)
      {
         weapon = obj;
      }
   }
   return weapon;
}

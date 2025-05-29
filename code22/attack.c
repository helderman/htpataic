#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "print.h"
#include "misc.h"
#include "match.h"
#include "noun.h"
#include "reach.h"
#include "damage.h"

static OBJECT *victimHere(void)
{
   OBJECT *victim = actorHere();
   if (victim == NULL)
   {
      printPrivate("There is nobody here to attack.\n");
   }
   return victim;
}

int executeAttack(void)
{
   OBJECT *victim =
      *params[0] == '\0' ? victimHere()
                         : reachableObject("who to attack", params[0]);
   if (victim != NULL)
   {
      OBJECT *weapon =
         *params[1] == '\0' ? getOptimalWeapon(player)
                            : getPossession(player, "wield", params[1]);
      if (weapon != NULL)
      {
         dealDamage(player, weapon, victim);
         return 1;
      }
   }
   return 0;
}

#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "print.h"
#include "misc.h"

static int weightOfContents(OBJECT *container)
{
   int sum = 0;
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (isHolding(container, obj)) sum += obj->weight;
   }
   return sum;
}

static void describeMove(OBJECT *obj, OBJECT *to)
{
   if (to == player->location)
   {
      printSee("You drop %s.\n", obj->description);
   }
   else if (to != player)
   {
      printAny(player, to, " see ", to->health > 0 ? "You give %s to %s.\n"
                                                   : "You put %s in %s.\n",
               obj->description, to->description);
      printAny(to, NULL, NULL, "You receive %s from %s.\n",
               obj->description, player->description);
   }
   else if (obj->location == player->location)
   {
      printSee("You pick up %s.\n", obj->description);
   }
   else
   {
      printSee("You get %s from %s.\n",
               obj->description, obj->location->description);
   }
}

int moveObject(OBJECT *obj, OBJECT *to)
{
   if (obj == NULL)
   {
      // already handled by getVisible or getPossession
      return 0;
   }
   else if (to == NULL)
   {
      printPrivate("There is nobody here to give that to.\n");
      return 0;
   }
   else if (obj->location != NULL && obj->location != player &&
            obj->location->health > 0 && obj->location->trust <= 0)
   {
      printPrivate("It seems %s feels reluctant to give you anything.\n",
                   obj->location->description);
      return 1;
   }
   else if (to->capacity == 0)
   {
      printPrivate(obj == keyForBox && (to == closedBox || to == lockedBox) ?
                      "The key seems to fit the lock.\n" :
                      "It doesn't seem to fit in.\n");
      return 1;
   }
   else if (obj->weight > to->capacity)
   {
      printPrivate("That is way too heavy.\n");
      return 1;
   }
   else if (obj->weight + weightOfContents(to) > to->capacity)
   {
      printPrivate("That would become too heavy.\n");
      return 1;
   }
   else
   {
      describeMove(obj, to);
      obj->location = to;
      return 1;
   }
}

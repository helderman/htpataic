#include <stdbool.h>
#include <stdio.h>
#include "object.h"
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
      printf("You drop %s.\n", obj->description);
   }
   else if (to != player)
   {
      printf(to->health > 0 ? "You give %s to %s.\n" : "You put %s in %s.\n",
             obj->description, to->description);
   }
   else if (obj->location == player->location)
   {
      printf("You pick up %s.\n", obj->description);
   }
   else
   {
      printf("You get %s from %s.\n",
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
      printf("There is nobody here to give that to.\n");
      return 0;
   }
   else if (obj->location != NULL && obj->location != player &&
            obj->location->health > 0 && obj->location->trust <= 0)
   {
      printf("It seems %s feels reluctant to give you anything.\n",
             obj->location->description);
      return 1;
   }
   else if (to->capacity == 0)
   {
      printf(obj == keyForBox && (to == closedBox || to == lockedBox) ?
                "The key seems to fit the lock.\n" :
                "It doesn't seem to fit in.\n");
      return 1;
   }
   else if (obj->weight > to->capacity)
   {
      printf("That is way too heavy.\n");
      return 1;
   }
   else if (obj->weight + weightOfContents(to) > to->capacity)
   {
      printf("That would become too heavy.\n");
      return 1;
   }
   else
   {
      describeMove(obj, to);
      obj->location = to;
      return 1;
   }
}

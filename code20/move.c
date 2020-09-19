#include <stdio.h>
#include "object.h"
#include "misc.h"

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
      if (to == player->location)
      {
         printf("You drop %s.\n", obj->description);
      }
      else if (to != player)
      {
         printf(to->health > 0 ? "You give %s to %s.\n"
                               : "You put %s in %s.\n",
                obj->description, to->description);
      }
      else if (obj->location == player->location)
      {
         printf("You pick up %s.\n", obj->description);
      }
      else
      {
         printf("You get %s from %s.\n", obj->description,
                                         obj->location->description);
      }
      obj->location = to;
      return 1;
   }
}

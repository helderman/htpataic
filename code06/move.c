#include <stdio.h>
#include "object.h"

void moveObject(OBJECT *obj, OBJECT *to)
{
   if (obj == NULL)
   {
      // already handled by getVisible or getPossession
   }
   else if (to == NULL)
   {
      printf("There is nobody here to give that to.\n");
   }
   else if (obj->location == NULL)
   {
      printf("That is way too heavy.\n");
   }
   else
   {
      if (to == player->location)
      {
         printf("You drop %s.\n", obj->description);
      }
      else if (to != player)
      {
         printf(to == guard ? "You give %s to %s.\n"
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
   }
}

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"

void moveObject(const char *noun, OBJECT *from, OBJECT *to)
{
   OBJECT *obj = matchingObject(noun);
   if (obj == NULL)
   {
      printf("I don't understand what item you mean.\n");
   }
   else if (from == NULL)
   {
      printf("I don't understand who you want to ask.\n");
   }
   else if (from != obj->location)
   {
      switch (distanceTo(obj))
      {
      case distPlayer:
         printf("You should not be doing that to yourself.\n");
         break;
      case distHeld:
         printf("You already have %s.\n", obj->description);
         break;
      case distLocation:
      case distOverthere:
         printf("That's not an item.\n");
         break;
      case distHere:
         if (from == player)
         {
            printf("You have no %s.\n", noun);
         }
         else
         {
            printf("Sorry, %s has no %s.\n", from->description, noun);
         }
         break;
      case distHereContained:
         printf("Sorry, %s is holding it.\n", obj->location->description);
         break;
      default:
         printf("You don't see any %s here.\n", noun);
      }
   }
   else if (to == NULL)
   {
      printf("There is nobody here to give that to.\n");
   }
   else if (obj->weight > to->capacity)
   {
      printf("That is way too heavy.\n");
   }
   else if (obj->weight + weightOfContents(to) > to->capacity)
   {
      printf("That would become too heavy.\n");
   }
   else
   {
      obj->location = to;
      printf("OK.\n");
   }
}

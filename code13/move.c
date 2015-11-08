#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"

bool moveObject(PARAM *par, OBJECT *from, OBJECT *to)
{
   OBJECT *obj = par->object;
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
      switch (par->distance)
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
            printf("You have no %s.\n", par->tag);
         }
         else
         {
            printf("Sorry, %s has no %s.\n", from->description, par->tag);
         }
         break;
      case distHeldContained:
      case distHereContained:
         printf("Sorry, %s is holding it.\n", obj->location->description);
         break;
      default:
         printf("You don't see any %s here.\n", par->tag);
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
   return true;
}

bool objectWithinReach(const char *verb, PARAM *par, OBJECT *acceptableLocation)
{
   int ok = false;
   if (par->distance > distNotHere)
   {
      printf("I don't understand what you want to %s.\n", verb);
   }
   else if (par->distance == distNotHere)
   {
      printf("You don't see any %s here.\n", par->tag);
   }
   else if (par->distance >= distHereContained &&
            par->object->location != acceptableLocation)
   {
      printf("That is out of reach.\n");
   }
   else if (par->count > 1)
   {
      printf("Multiple choices to %s; be more specific.\n", verb);
   }
   else
   {
      ok = true;
   }
   return ok;
}

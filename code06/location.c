#include <stdio.h>
#include <string.h>
#include "object.h"
#include "misc.h"
#include "noun.h"

void executeLook(const char *noun)
{
   if (noun != NULL && strcmp(noun, "around") == 0)
   {
      printf("You are in %s.\n", player->location->description);
      listObjectsAtLocation(player->location);
   }
   else
   {
      printf("I don't understand what you want to see.\n");
   }
}

void executeGo(const char *noun)
{
   OBJECT *obj = getVisible("where you want to go", noun);
   if (obj == NULL)
   {
      // already handled by getVisible
   }
   else if (getPassage(player->location, obj) != NULL)
   {
      printf("OK.\n");
      player->location = obj;
      executeLook("around");
   }
   else if (obj->location != player->location)
   {
      printf("You don't see any %s here.\n", noun);
   }
   else if (obj->destination != NULL)
   {
      printf("OK.\n");
      player->location = obj->destination;
      executeLook("around");
   }
   else
   {
      printf("You can't get much closer than this.\n");
   }
}

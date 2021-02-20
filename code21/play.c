#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "match.h"
#include "noun.h"
#include "location.h"

int executePlay(void)
{
   OBJECT *obj = getTopic(params[0]);
   if (obj == NULL)
   {
      printf("I don't understand what character you want to play.\n");
   }
   else if (obj == player)
   {
      printf("You already are %s.\n", player->description);
   }
   else if (obj == jack || obj == jill)
   {
      player = obj;
      printf("You are %s. %s\n", player->description, player->details);
   }
   else
   {
      printf("That is not a character you can play.\n");
   }
   return 0;
}

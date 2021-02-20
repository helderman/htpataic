#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "print.h"
#include "match.h"
#include "noun.h"
#include "location.h"

int executePlay(void)
{
   OBJECT *obj = getTopic(params[0]);
   if (obj == NULL)
   {
      printPrivate("I don't understand what character you want to play.\n");
   }
   else if (obj == player)
   {
      printPrivate("You already are %s.\n", player->description);
   }
   else if (obj == jack || obj == jill)
   {
      player = obj;
      printPrivate("You are %s. %s\n", player->description, player->details);
   }
   else
   {
      printPrivate("That is not a character you can play.\n");
   }
   return 0;
}

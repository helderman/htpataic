#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "print.h"
#include "match.h"
#include "noun.h"
#include "location.h"

int executePlay(void)
{
   OBJECT *who = getTopic(params[0]);
   if (who != NULL)
   {
      player = who;
      printPrivate("You are %s.\n", player->description);
      printPrivate("%s\n", player->details);
      executeLookAround();
   }
   else
   {
      printPrivate("I don't know that character.\n");
   }
   return 0;
}

#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "print.h"
#include "match.h"
#include "noun.h"
#include "reach.h"
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

int executeEmote(void)
{
   const char *phrase = params[0];
   if (*phrase == '\0')
   {
      printPrivate("I don't understand what you want to emote.\n");
   }
   else
   {
      printAny(player, NULL, " see ", "You %s\n", phrase);
   }
   return 0;
}

int executeSay(void)
{
   const char *phrase = params[0];
   if (*phrase == '\0')
   {
      printPrivate("I don't understand what you want to say.\n");
   }
   else
   {
      printAny(player, NULL, " hear ", "You say: %s\n", phrase);
   }
   return 0;
}

int executeWhisper(void)
{
   OBJECT *to = reachableObject("who to whisper to", params[1]);
   if (to != NULL)
   {
      const char *phrase = params[0];
      if (*phrase == '\0')
      {
         printPrivate("I don't understand what you want to whisper.\n");
      }
      else
      {
         printAny(to, NULL, NULL, "You hear %s whisper to you: %s\n",
                  player->description, phrase);
         printAny(player, to, " hear ", "You whisper something to %s.\n",
                  to->description);
      }
   }
   return 0;
}

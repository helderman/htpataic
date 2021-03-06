#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "match.h"
#include "noun.h"
#include "reach.h"
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

int executeEmote(void)
{
   const char *phrase = params[0];
   if (*phrase == '\0')
   {
      printf("I don't understand what you want to emote.\n");
   }
   else
   {
      printf("You %s\n", phrase);
   }
   return 0;
}

int executeSay(void)
{
   const char *phrase = params[0];
   if (*phrase == '\0')
   {
      printf("I don't understand what you want to say.\n");
   }
   else
   {
      printf("You say: %s\n", phrase);
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
         printf("I don't understand what you want to whisper.\n");
      }
      else
      {
         printf("You whisper to %s: %s\n", to->description, phrase);
      }
   }
   return 0;
}

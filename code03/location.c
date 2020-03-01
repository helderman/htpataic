#include <stdio.h>
#include <string.h>

struct location {
   const char *description;
   const char *tag;
}
locs[] = {
   {"an open field", "field"},
   {"a little cave", "cave"}
};

#define numberOfLocations   (sizeof locs / sizeof *locs)

static unsigned locationOfPlayer = 0;

void executeLook(const char *noun)
{
   if (noun != NULL && strcmp(noun, "around") == 0)
   {
      printf("You are in %s.\n", locs[locationOfPlayer].description);
   }
   else
   {
      printf("I don't understand what you want to see.\n");
   }
}

void executeGo(const char *noun)
{
   unsigned i;
   for (i = 0; i < numberOfLocations; i++)
   {
      if (noun != NULL && strcmp(noun, locs[i].tag) == 0)
      {
         if (i == locationOfPlayer)
         {
            printf("You can't get much closer than this.\n");
         }
         else
         {
            printf("OK.\n");
            locationOfPlayer = i;
            executeLook("around");
         }
         return;
      }
   }
   printf("I don't understand where you want to go.\n");
}

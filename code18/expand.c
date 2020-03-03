#include <stdbool.h>
#include <string.h>
#include "match.h"

typedef struct
{
   const char *abbreviated;
   const char *expanded;
} SHORTHAND;

static int minimum(int x, int y)
{
   return x < y ? x : y;
}

char *expand(char *input, int bufsize)
{
   static const SHORTHAND shorthands[] =
   {
      {"n", "go north"},
      {"s", "go south"},
      {"w", "go west"},
      {"e", "go east"},
      {"inv", "inventory"},
      {"x A", "examine "},
      {"A", NULL}
   };
   const SHORTHAND *sh;
   for (sh = shorthands; !matchCommand(input, sh->abbreviated); sh++);
   if (sh->expanded != NULL)
   {
      const char *moreInput = *paramByLetter('A');
      int lengthOfExpanded = strlen(sh->expanded);
      memmove(input + lengthOfExpanded, moreInput,
              minimum(strlen(moreInput) + 1, bufsize - lengthOfExpanded - 1));
      strncpy(input, sh->expanded, lengthOfExpanded);
   }
   return input;
}

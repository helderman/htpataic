#include <stdbool.h>
#include <stdio.h>
#include <string.h>


bool parseAndExecute(char *input)
{
   char *verb = strtok(input, " \n");
   char *noun = strtok(NULL, " \n");
  (void) noun;
   if (verb != NULL)
   {
      if (strcmp(verb, "quit") == 0)
      {
         return false;
      }
      else if (strcmp(verb, "look") == 0)
      {
         printf("It is very dark in here.\n");
      }
      else if (strcmp(verb, "go") == 0)
      {
         printf("It's too dark to go anywhere.\n");
      }
      else
      {
         printf("I don't know how to '%s'.\n", verb);
      }
   }
   return true;
}

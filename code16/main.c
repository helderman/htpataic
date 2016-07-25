#include <stdio.h>
#include <stdbool.h>
#include "parsexec.h"

static char input[100] = "look around";

static bool getInput(const char *filename)
{
   static FILE *fp = NULL;
   bool ok;
   if (fp == NULL)
   {
      if (filename != NULL) fp = fopen(filename, "rt");
      if (fp == NULL) fp = stdin;
   }
   else if (fp == stdin)
   {
      FILE *out = fopen(filename, "at");
      if (out != NULL)
      {
         fprintf(out, "%s", input);
         fclose(out);
      }
   }
   printf("\n--> ");
   ok = fgets(input, sizeof(input), fp) != NULL;
   if (fp != stdin)
   {
      if (ok)
      {
         printf("%s", input);
      }
      else
      {
         fclose(fp);
         ok = fgets(input, sizeof(input), fp = stdin) != NULL;
      }
   }
   return ok;
}

int main(int argc, char *argv[])
{
   printf("Welcome to Little Cave Adventure.\n");
   while (parseAndExecute(input) && getInput(argv[1]));
   printf("\nBye!\n");
   return 0;
}

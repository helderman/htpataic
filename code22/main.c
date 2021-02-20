#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "print.h"
#include "object.h"
#include "match.h"
#include "noun.h"
#include "expand.h"
#include "parsexec.h"
#include "turn.h"
#include "server.h"

static char input[100] = "look around";

static int time;

static bool getFromFP(FILE *fp)
{
   bool ok = fgets(input, sizeof input, fp) != NULL;
   if (ok) input[strcspn(input, "\n")] = '\0';
   return ok;
}

static bool getInput(const char *filename)
{
   static FILE *fp = NULL;
   bool ok;
   if (fp == NULL)
   {
      if (filename != NULL) fp = fopen(filename, "rt");
      if (fp == NULL) fp = stdin;
   }
   else if (fp == stdin && filename != NULL)
   {
      FILE *out = fopen(filename, "at");
      if (out != NULL)
      {
         fprintf(out, "%s\n", input);
         fclose(out);
      }
   }
   printf("\n--> ");
   ok = getFromFP(fp);
   if (fp != stdin)
   {
      if (ok)
      {
         printf("%s\n", input);
      }
      else
      {
         fclose(fp);
         ok = getFromFP(fp = stdin);
      }
   }
   return ok;
}

static bool processCommand(char *ptr, int size)
{
   return turn(parseAndExecute(expand(ptr, size)));
}

static bool adminProcessCommand(void)
{
   if (matchCommand(input, "@A B"))
   {
      player = getTopic(params[0]);
      sscanf(params[1], "%d", &time);
      return true;
   }
   else
   {
      return processCommand(input, sizeof input);
   }
}

int main(int argc, char *argv[])
{
   (void)argc;
   printf("Welcome to Little Cave Adventure.\n");
   printf("You are in single-user mode; enter 'quit' for multi-user mode.\n");
   player = nobody;
   while (adminProcessCommand() && getInput(argv[1]));
   printf("\nGoing into multi-user mode; press ^C to stop.\n");
   server(processCommand);
   printf("\nBye!\n");
   return 0;
}

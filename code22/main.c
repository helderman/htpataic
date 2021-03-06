#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "object.h"
#include "print.h"
#include "expand.h"
#include "parsexec.h"
#include "turn.h"
#include "server.h"

static char input[100] = "look around";

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
   printConsole("\n--> ");
   ok = getFromFP(fp);
   if (fp != stdin)
   {
      if (ok)
      {
         printConsole("%s\n", input);
      }
      else
      {
         fclose(fp);
         ok = getFromFP(fp = stdin);
      }
   }
   return ok;
}

static bool processInput(char *ptr, int size)
{
   return turn(parseAndExecute(expand(ptr, size)));
}

int main(int argc, char *argv[])
{
   (void)argc;
   printConsole("Welcome to Little Cave Adventure.\n");
   printConsole("You are in single-user mode; enter 'quit' for multi-user.\n");
   player = nobody;
   while (processInput(input, sizeof input) && getInput(argv[1]));
   printConsole("\nGoing into multi-user mode; press ^C to stop.\n");
   server(processInput);
   printConsole("\nBye!\n");
   return 0;
}

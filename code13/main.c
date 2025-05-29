#include <stdbool.h>
#include <stdio.h>
#include "parsexec.h"

static char input[100] = "look around";

static bool getInput(void)
{
   printf("\n--> ");
   return fgets(input, sizeof input, stdin) != NULL;
}

int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;
   printf("Welcome to Little Cave Adventure.\n");
   while (parseAndExecute(input) && getInput());
   printf("\nBye!\n");
   return 0;
}

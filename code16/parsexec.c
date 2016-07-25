#include <ctype.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "location.h"
#include "execute.h"

typedef struct
{
   bool (*function)(void);
   const char *pattern;
} COMMAND;

static bool executeQuit(void)
{
   return false;
}

static bool executeNoMatch(void)
{
   const char *src = *params;
   if (*src != '\0')
   {
      printf("I don't know how to '");
      while (*src != '\0' && !isspace(*src)) putchar(*src++);
      printf("'.\n");
   }
   return true;
}

bool parseAndExecute(const char *input)
{
   static const COMMAND commands[] =
   {
      {executeQuit      , "quit"},
      {executeLookAround, "look"},
      {executeLookAround, "look around"},
      {executeLook      , "look at A"},
      {executeLook      , "look A"},
      {executeGo        , "go to A"},
      {executeGo        , "go A"},
      {executeGetFrom   , "get A from B"},
      {executeGet       , "get A"},
      {executePutIn     , "put A in B"},
      {executePutIn     , "drop A in B"},
      {executeDrop      , "drop A"},
      {executeAskFrom   , "ask A from B"},
      {executeAsk       , "ask A"},
      {executeGiveTo    , "give A to B"},
      {executeGive      , "give A"},
      {executeInventory , "inventory"},
      {executeOpen      , "open A"},
      {executeClose     , "close A"},
      {executeLock      , "lock A"},
      {executeUnlock    , "unlock A"},
      {executeTurnOn    , "turn on A"},
      {executeTurnOff   , "turn off A"},
      {executeTurnOn    , "turn A on"},
      {executeTurnOff   , "turn A off"},
      {executeNoMatch   , "A"}
   };
   const COMMAND *cmd;
   for (cmd = commands; !matchCommand(input, cmd->pattern); cmd++);
   return (*cmd->function)();
}

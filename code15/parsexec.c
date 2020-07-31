#include <ctype.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "location.h"
#include "inventory.h"
#include "inventory2.h"
#include "openclose.h"
#include "onoff.h"

typedef struct
{
   const char *pattern;
   bool (*function)(void);
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
      { "quit"                , executeQuit       },
      { "look"                , executeLookAround },
      { "look around"         , executeLookAround },
      { "look at A"           , executeLook       },
      { "look A"              , executeLook       },
      { "examine A"           , executeLook       },
      { "go to A"             , executeGo         },
      { "go A"                , executeGo         },
      { "get A from B"        , executeGetFrom    },
      { "get A"               , executeGet        },
      { "put A in B"          , executePutIn      },
      { "drop A in B"         , executePutIn      },
      { "drop A"              , executeDrop       },
      { "ask A from B"        , executeAskFrom    },
      { "ask A"               , executeAsk        },
      { "give A to B"         , executeGiveTo     },
      { "give A"              , executeGive       },
      { "inventory"           , executeInventory  },
      { "open A"              , executeOpen       },
      { "close A"             , executeClose      },
      { "lock A"              , executeLock       },
      { "unlock A"            , executeUnlock     },
      { "turn on A"           , executeTurnOn     },
      { "turn off A"          , executeTurnOff    },
      { "turn A on"           , executeTurnOn     },
      { "turn A off"          , executeTurnOff    },
      { "A"                   , executeNoMatch    }
   };
   const COMMAND *cmd;
   for (cmd = commands; !matchCommand(input, cmd->pattern); cmd++);
   return (*cmd->function)();
}

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "location.h"
#include "inventory.h"
#include "inventory2.h"
#include "openclose.h"
#include "onoff.h"
#include "talk.h"
#include "attack.h"

typedef struct
{
   const char *pattern;
   int (*function)(void);
} COMMAND;

static int executeQuit(void)
{
   return -1;
}

static int executeNoMatch(void)
{
   const char *src = *params;
   int len;
   for (len = 0; src[len] != '\0' && !isspace(src[len]); len++);
   if (len > 0) printf("I don't know how to '%.*s'.\n", len, src);
   return 0;
}

static int executeWait(void)
{
   printf("Some time passes...\n");
   return 1;
}

int parseAndExecute(const char *input)
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
      { "talk with B about A" , executeTalkTo     },
      { "talk about A with B" , executeTalkTo     },
      { "talk about A"        , executeTalk       },
      { "talk A"              , executeTalk       },
      { "attack with B"       , executeAttack     },
      { "attack A with B"     , executeAttack     },
      { "attack A"            , executeAttack     },
      { "wait"                , executeWait       },
      { "A"                   , executeNoMatch    }
   };
   const COMMAND *cmd;
   for (cmd = commands; !matchCommand(input, cmd->pattern); cmd++);
   return (*cmd->function)();
}

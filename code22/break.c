#include <stdbool.h>
#include <string.h>
#include <signal.h>

static volatile sig_atomic_t done = 0;

static void handler(int signum)
{
   done = signum;
}

void breakInit(void)
{
   struct sigaction action;
   memset(&action, 0, sizeof(action));
   action.sa_handler = handler;
   sigaction(SIGINT, &action, NULL);
   sigaction(SIGTERM, &action, NULL);
}

bool breakTest(void)
{
   return done == 0;
}

int breakSignalNumber(void)
{
   return done;
}

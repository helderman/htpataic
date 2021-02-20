#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "location.h"

static void swapLocations(const char *verb1, OBJECT *obj1,
                          const char *verb2, OBJECT *obj2)
{
   OBJECT *tmp = obj1->location;
   OBJECT *obj = tmp != NULL ? obj1 : obj2;
   const char *verb = tmp != NULL ? verb1 : verb2;
   obj1->location = obj2->location;
   obj2->location = tmp;
   if (verb != NULL) printf("You %s %s.\n", verb, obj->description);
}

void cannotBeOpened(void)    { printf("That cannot be opened.\n");    }
void cannotBeClosed(void)    { printf("That cannot be closed.\n");    }
void cannotBeLocked(void)    { printf("That cannot be locked.\n");    }
void cannotBeUnlocked(void)  { printf("That cannot be unlocked.\n");  }

void isAlreadyOpen(void)     { printf("That is already open.\n");     }
void isAlreadyClosed(void)   { printf("That is already closed.\n");   }
void isAlreadyLocked(void)   { printf("That is already locked.\n");   }
void isAlreadyUnlocked(void) { printf("That is already unlocked.\n"); }

void isStillOpen(void)       { printf("That is still open.\n");       }
void isStillLocked(void)     { printf("That is locked.\n");           }

void toggleDoorToBackroom(void)
{
   swapLocations(NULL, openDoorToCave, NULL, closedDoorToCave);
   swapLocations("close", openDoorToBackroom, "open", closedDoorToBackroom);
}

void toggleDoorToCave(void)
{
   swapLocations(NULL, openDoorToBackroom, NULL, closedDoorToBackroom);
   swapLocations("close", openDoorToCave, "open", closedDoorToCave);
}

void toggleBox(void)
{
   swapLocations("close", openBox, "open", closedBox);
}

void toggleBoxLock(void)
{
   if (keyForBox->location == player)
   {
      swapLocations("lock", closedBox, "unlock", lockedBox);
   }
   else
   {
      printf("You don't have a key.\n");
   }
}

void toggleLamp(void)
{
   bool oldLit = isLit(player->location);
   swapLocations("turn off", lampOn, "turn on", lampOff);
   if (oldLit != isLit(player->location))
   {
      printf("\n");
      executeLookAround();
   }
}

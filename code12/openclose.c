#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "reach.h"

void executeOpen(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to open", noun);
   if (obj != NULL) (*obj->open)();
}

void executeClose(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to close", noun);
   if (obj != NULL) (*obj->close)();
}

void executeLock(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to lock", noun);
   if (obj != NULL) (*obj->lock)();
}

void executeUnlock(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to unlock", noun);
   if (obj != NULL) (*obj->unlock)();
}

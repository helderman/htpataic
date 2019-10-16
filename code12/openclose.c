#include <stdio.h>
#include "object.h"
#include "reach.h"

void executeOpen(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to open", noun);
   if (obj != NULL) printf("%s", (*obj->open)());
}

void executeClose(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to close", noun);
   if (obj != NULL) printf("%s", (*obj->close)());
}

void executeLock(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to lock", noun);
   if (obj != NULL) printf("%s", (*obj->lock)());
}

void executeUnlock(const char *noun)
{
   OBJECT *obj = reachableObject("what you want to unlock", noun);
   if (obj != NULL) printf("%s", (*obj->unlock)());
}

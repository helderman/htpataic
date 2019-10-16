#include <stdio.h>
#include "object.h"
#include "match.h"
#include "reach.h"

bool executeOpen(void)
{
   OBJECT *obj = reachableObject("what you want to open", params[0]);
   if (obj != NULL) printf("%s", (*obj->open)());
   return true;
}

bool executeClose(void)
{
   OBJECT *obj = reachableObject("what you want to close", params[0]);
   if (obj != NULL) printf("%s", (*obj->close)());
   return true;
}

bool executeLock(void)
{
   OBJECT *obj = reachableObject("what you want to lock", params[0]);
   if (obj != NULL) printf("%s", (*obj->lock)());
   return true;
}

bool executeUnlock(void)
{
   OBJECT *obj = reachableObject("what you want to unlock", params[0]);
   if (obj != NULL) printf("%s", (*obj->unlock)());
   return true;
}

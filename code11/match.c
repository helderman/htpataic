#include <string.h>
#include "object.h"
#include "misc.h"

static bool nounIsInTags(const char *noun, const char **tags)
{
   while (*tags != NULL)
   {
      if (strcmp(noun, *tags++) == 0) return true;
   }
   return false;
}

OBJECT *matchingObject(const char *noun)
{
   OBJECT *obj, *found = NULL;
   forEachObject(obj)
   {
      if (noun != NULL && nounIsInTags(noun, obj->tags) &&
          distanceTo(obj) < distanceTo(found))
      {
         found = obj;
      }
   }
   return found;
}

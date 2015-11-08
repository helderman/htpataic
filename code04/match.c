#include <string.h>
#include "object.h"

OBJECT *matchingObject(const char *noun)
{
   OBJECT *obj, *found = NULL;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (noun != NULL && strcmp(noun, obj->tag) == 0)
      {
         found = obj;
      }
   }
   return found;
}

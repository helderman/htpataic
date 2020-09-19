#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "object.h"
#include "misc.h"
#include "match.h"

const char *params[MAX_PARAMS];

static const char *skipSpaces(const char *src)
{
   while (isspace(*src)) src++;
   return src;
}

static const char *matchSpaces(const char *src)
{
   return *src == '\0' || isspace(*src) ? skipSpaces(src) : NULL;
}

static const char *matchTerminal(const char *src, char terminal)
{
   return terminal == ' '                    ? matchSpaces(src) :
          tolower(*src) == tolower(terminal) ? src + 1          : NULL;
}

static const char *matchTag(const char *src, const char *tag, bool atEnd)
{
   while (src != NULL && *tag != '\0')
   {
      src = matchTerminal(src, *tag++);
   }
   return atEnd && src != NULL && *skipSpaces(src) != '\0' ? NULL : src;
}

static const char *matchParam(const char *src, const char **par, bool loose)
{
   const char *restOfSrc = loose ? src + strlen(src) : NULL;
   OBJECT *obj;
   forEachObject(obj)
   {
      const char **tag;
      for (tag = obj->tags; *tag != NULL; tag++)
      {
         const char *behindMatch = matchTag(src, *tag, loose);
         if (behindMatch != NULL && strlen(*tag) > strlen(*par))
         {
            *par = *tag;
            restOfSrc = behindMatch;
         }
      }
   }
   if (**par == '\0')
   {
      *par = src;
   }
   return restOfSrc;
}

bool matchCommand(const char *src, const char *pattern)
{
   const char **par;
   for (par = params; par < params + MAX_PARAMS; par++)
   {
      *par = "";
   }
   for (src = skipSpaces(src); src != NULL && *pattern != '\0'; pattern++)
   {
      src = isupper(*pattern)
               ? matchParam(src, paramByLetter(*pattern), pattern[1] == '\0')
               : matchTerminal(src, *pattern);
   }
   return src != NULL && *skipSpaces(src) == '\0';
}

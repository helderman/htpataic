#include <ctype.h>
#include <string.h>
#include "object.h"
#include "misc.h"
#include "match.h"

#define MAX_PARAMS  26

PARAM params[MAX_PARAMS];

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

static const char *matchTag(const char *src, const char *tag, int atEnd)
{
   while (src != NULL && *tag != '\0') src = matchTerminal(src, *tag++);
   return atEnd && src != NULL && *skipSpaces(src) != '\0' ? NULL : src;
}

static int isBetterMatch(const char *tag, DISTANCE distance, PARAM *par)
{
   int difference = strlen(tag) - strlen(par->tag);
   if (difference == 0) difference = par->distance - distance;
   if (difference == 0) par->count++;
   return difference > 0;
}

static const char *matchParam(const char *src, PARAM *par, int loose)
{
   const char *restOfSrc = loose ? src + strlen(src) : NULL;
   OBJECT *obj;
   par->src = src;
   par->distance = *src == '\0' ? distNoObjectSpecified : distUnknownObject;
   forEachObject(obj)
   {
      DISTANCE distance = distanceTo(obj);
      const char **tag;
      for (tag = obj->tags; *tag != NULL; tag++)
      {
         const char *behindMatch = matchTag(src, *tag, loose);
         if (behindMatch != NULL && isBetterMatch(*tag, distance, par))
         {
            par->tag = *tag;
            par->object = obj;
            par->distance = distance;
            par->count = 1;
            restOfSrc = behindMatch;
         }
      }
   }
   return restOfSrc;
}

int matchCommand(const char *src, const char *pattern)
{
   PARAM *par;
   for (par = params; par < params + MAX_PARAMS; par++)
   {
      par->tag = "";
      par->object = NULL;
      par->distance = distNoObjectSpecified;
      par->count = 0;
   }
   for (src = skipSpaces(src); src != NULL && *pattern != '\0'; pattern++)
   {
      src = isupper(*pattern) ? matchParam(src, paramByLetter(*pattern),
                                           pattern[1] == '?') :
            *pattern == '?'   ? src :
                                matchTerminal(src, *pattern);
   }
   return src != NULL && *skipSpaces(src) == '\0';
}

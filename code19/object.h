#include <stdbool.h>

typedef struct object {
   bool         (*condition)(void);
   const char    *description;
   const char   **tags;
   struct object *location;
   struct object *destination;
   struct object *prospect;
   const char    *details;
   const char    *contents;
   const char    *textGo;
   const char    *gossip;
   int            weight;
   int            capacity;
   int            health;
   const char  *(*open)(void);
   const char  *(*close)(void);
   const char  *(*lock)(void);
   const char  *(*unlock)(void);
} OBJECT;

extern OBJECT objs[];

#define gossipEWNS	(objs + 0)
#define field	(objs + 1)
#define cave	(objs + 2)
#define silver	(objs + 3)
#define gold	(objs + 4)
#define guard	(objs + 5)
#define player	(objs + 6)
#define intoCave	(objs + 7)
#define intoCaveBlocked	(objs + 8)
#define exitCave	(objs + 9)
#define wallField	(objs + 10)
#define wallCave	(objs + 11)
#define backroom	(objs + 12)
#define wallBackroom	(objs + 13)
#define openDoorToBackroom	(objs + 14)
#define closedDoorToBackroom	(objs + 15)
#define openDoorToCave	(objs + 16)
#define closedDoorToCave	(objs + 17)
#define openBox	(objs + 18)
#define closedBox	(objs + 19)
#define lockedBox	(objs + 20)
#define keyForBox	(objs + 21)
#define lampOff	(objs + 22)
#define lampOn	(objs + 23)

#define endOfObjs	(objs + 24)

#define validObject(obj)	((obj) != NULL && (*(obj)->condition)())

#define forEachObject(obj)	for (obj = objs; obj < endOfObjs; obj++) if (validObject(obj))

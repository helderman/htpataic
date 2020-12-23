
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
   int            weight;
   int            capacity;
   int            health;
   const char  *(*open)(void);
   const char  *(*close)(void);
   const char  *(*lock)(void);
   const char  *(*unlock)(void);
} OBJECT;

extern OBJECT objs[];

#define field	(objs + 0)
#define cave	(objs + 1)
#define silver	(objs + 2)
#define gold	(objs + 3)
#define guard	(objs + 4)
#define player	(objs + 5)
#define intoCave	(objs + 6)
#define intoCaveBlocked	(objs + 7)
#define exitCave	(objs + 8)
#define wallField	(objs + 9)
#define wallCave	(objs + 10)
#define backroom	(objs + 11)
#define wallBackroom	(objs + 12)
#define openDoorToBackroom	(objs + 13)
#define closedDoorToBackroom	(objs + 14)
#define openDoorToCave	(objs + 15)
#define closedDoorToCave	(objs + 16)
#define openBox	(objs + 17)
#define closedBox	(objs + 18)
#define lockedBox	(objs + 19)
#define keyForBox	(objs + 20)

#define endOfObjs	(objs + 21)

#define validObject(obj)	((obj) != NULL && (*(obj)->condition)())


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
   int            light;
   int            impact;
   int            trust;
   void         (*open)(void);
   void         (*close)(void);
   void         (*lock)(void);
   void         (*unlock)(void);
} OBJECT;

extern OBJECT *player, objs[];

#define heaven	(objs + 0)
#define respawn	(objs + 1)
#define heavenEWNS	(objs + 2)
#define waitingRoom	(objs + 3)
#define waitingRoomWall	(objs + 4)
#define nobody	(objs + 5)
#define field	(objs + 6)
#define cave	(objs + 7)
#define silver	(objs + 8)
#define gold	(objs + 9)
#define guard	(objs + 10)
#define jack	(objs + 11)
#define jill	(objs + 12)
#define intoCave	(objs + 13)
#define intoCaveBlocked	(objs + 14)
#define exitCave	(objs + 15)
#define wallField	(objs + 16)
#define wallCave	(objs + 17)
#define backroom	(objs + 18)
#define wallBackroom	(objs + 19)
#define openDoorToBackroom	(objs + 20)
#define closedDoorToBackroom	(objs + 21)
#define openDoorToCave	(objs + 22)
#define closedDoorToCave	(objs + 23)
#define openBox	(objs + 24)
#define closedBox	(objs + 25)
#define lockedBox	(objs + 26)
#define keyForBox	(objs + 27)
#define lampOff	(objs + 28)
#define lampOn	(objs + 29)
#define club	(objs + 30)
#define dagger	(objs + 31)

#define endOfObjs	(objs + 32)

#define validObject(obj)	((obj) != NULL && (*(obj)->condition)())

typedef enum {
   distSelf,
   distHeld,
   distHeldContained,
   distLocation,
   distHere,
   distHereContained,
   distOverthere,
   distNotHere,
   distUnknownObject
} DISTANCE;

extern bool isHolding(OBJECT *container, OBJECT *obj);
extern OBJECT *getPassage(OBJECT *from, OBJECT *to);
extern DISTANCE getDistance(OBJECT *from, OBJECT *to);
extern OBJECT *actorHere(void);
extern int listObjectsAtLocation(OBJECT *location);

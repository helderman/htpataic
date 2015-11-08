typedef enum {
   distPlayer,
   distHeld,
   distHeldContained,
   distLocation,
   distHere,
   distHereContained,
   distOverthere,
   distNotHere,
   distUnknownObject,
   distNoObjectSpecified
} DISTANCE;

extern OBJECT *getPassageTo(OBJECT *targetLocation);
extern DISTANCE distanceTo(OBJECT *obj);
extern OBJECT *actorHere(void);
extern int listObjectsAtLocation(OBJECT *location);
extern int weightOfContents(OBJECT *container);

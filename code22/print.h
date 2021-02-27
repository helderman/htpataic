extern void printSetCurrent(int fd);
extern void printConsole(const char *format, ...);
extern void printPrivate(const char *format, ...);
extern void printHear(const char *format, ...);
extern void printSee(const char *format, ...);
extern void printAny(OBJECT *obj1, OBJECT *obj2, const char *sense,
                     const char *format, ...);

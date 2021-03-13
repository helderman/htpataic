typedef struct
{
   bool iac;
   int negotiate;
   unsigned index;
   char data[100];
}
INBUF;

extern void telnetInit(INBUF *inbuf);
extern void telnetConfigure(void);
extern void telnetInsertSpaces(INBUF *inbuf);
extern void telnetDeleteSpaces(INBUF *inbuf);
extern void telnetAppendPrompt(INBUF *inbuf);
extern void telnetDeletePrompt(INBUF *inbuf);
extern void telnetParse(INBUF *inbuf, int fd, void (*action)(char *, int),
                        const char *data, int length);

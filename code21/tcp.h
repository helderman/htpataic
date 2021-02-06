extern int tcpListen(struct sockaddr_in *addr, uint16_t port);
extern int tcpAccept(struct sockaddr_in *addr, int listener);
extern void tcpSend(int fd, const char *data, int len);

extern int tcpListen(struct sockaddr_in *addr, uint16_t port);
extern int tcpAccept(struct sockaddr_in *addr, int listener);

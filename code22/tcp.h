extern int tcpListen(struct sockaddr_in *addr, uint16_t port);
extern void tcpClose(int fd, uint16_t port);
extern int tcpSelect(int nfds, fd_set *readfds);
extern int tcpAccept(struct sockaddr_in *addr, int listener);
extern void tcpDisconnect(int fd);
extern void tcpSend(int fd, const char *data, int len);

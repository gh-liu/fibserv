#include <sys/socket.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

typedef struct {
  int threadCount;
} serverSettings;

typedef struct {
  int serverFd;
  sockaddr *addr;
  socklen_t *addrLen;
} acceptParams;

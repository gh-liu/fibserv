#include "../libs/helpers.h"
#include "../libs/macros.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

noreturn void *acceptConn(void *arg) {
  acceptParams *ap = (acceptParams *)arg;
  int acceptedSocket;
  while (1) {
    if ((acceptedSocket = accept(ap->serverFd, ap->addr, ap->addrLen)) < 0) {
      perror("In accept");
      // pthread_exit(NULL);
    }

    char reqBuf[HTTP_REQ_BUF];
    bzero(reqBuf, HTTP_REQ_BUF);
    const size_t receivedBytes = read(acceptedSocket, reqBuf, HTTP_REQ_BUF);

    if (receivedBytes > 0) {
      char respBuf[HTTP_RESP_BUF];
      const int num = retrieveGETQueryIntValByKey(reqBuf, "num");

      int result = calcFibonacci(num);

      sprintf(respBuf,
              "HTTP/1.1 200 OK\r\n"
              "Content-type: text/plain\r\n"
              "Content-length: %d\r\n\r\n%d",
              calcDigits(result), result);
    }

    close(acceptedSocket);
  }
}

int main(int argc, char *argv[]) {
  int serverFd;
  sockaddr_in address;
  int addrLen = sizeof(address);

  if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("In socket creation");
    exit(EXIT_FAILURE);
  }

  bzero(&address, addrLen);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(serverFd, (sockaddr *)&address, sizeof(address)) < 0) {
    perror("In bind");
    exit(EXIT_FAILURE);
  }

  if (listen(serverFd, MAX_LISTEN_CONN) < 0) {
    perror("In listen");
    exit(EXIT_FAILURE);
  }

  while (1) {
    int acceptedSocket;
    if ((acceptedSocket = accept(serverFd, (sockaddr *)&address,
                                 (socklen_t *)&addrLen)) < 0) {
      perror("In accept");
      // pthread_exit(NULL);
    }

    char reqBuf[HTTP_REQ_BUF];
    bzero(reqBuf, HTTP_REQ_BUF);
    const size_t receivedBytes = read(acceptedSocket, reqBuf, HTTP_REQ_BUF);
    if (receivedBytes > 0) {
      char respBuf[HTTP_RESP_BUF];
      write(receivedBytes, respBuf, strlen(respBuf));
    }
  }

  return EXIT_SUCCESS;
}

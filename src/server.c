#include <netinet/in.h>  // struct sockaddr_in
#include <stdio.h>       // printf()
#include <string.h>      // strlen()
#include <sys/socket.h>  // socket, sedsockopt
#include <unistd.h>      // close(fd)

#include "log.h"

static void do_something(int connfd) {
  char rbuf[64] = {};
  ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
  if (n < 0) {
    msg("read() error");
    return;
  }
  printf("client says: %s\n", rbuf);

  char wbuf[] = "world";
  write(connfd, wbuf, strlen(wbuf));
}

void start_server() {
  int fd = socket(AF_INET /* IPv4 */, SOCK_STREAM /* TCP */, 0);
  int val = 1;
  // SO_REUSEADDR: no time wait protection
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

  // bind, this is the syntax that deals with IPv4 address
  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
	// Network TO Host Short, usually for set port, need a 16-bit-value
  addr.sin_port = ntohs(1234);
	// Network TO Host Long, usually for set address, need a 32-bit-value
  addr.sin_addr.s_addr = ntohl(0);  // wildcard address 0.0.0.0
  int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
  if (rv) {
    die("bind()");
  }

  // listen
  rv = listen(fd, SOMAXCONN);
  if (rv) {
    die("listen()");
  }

  while (1) {
    // accept
    struct sockaddr_in client_addr = {};
    socklen_t addrlen = sizeof(client_addr);
    int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
    if (connfd < 0) {
      continue;  // error
    }

    do_something(connfd);
    close(connfd);
  }
}

int main(int argc, char **argv) {
  start_server();
  return 0;
}
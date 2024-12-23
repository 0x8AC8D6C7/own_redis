#include <netinet/in.h>  // struct sockaddr_in
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>  // socket(), setsockopt()
#include <unistd.h>

#include "log.h"

void start_client() {
  int fd = socket(AF_INET /* IPv4 */, SOCK_STREAM /* TCP */, 0);
  if (fd < 0) {
    die("socket()");
  }

  // Socket Address INternet, for IPv5 only.
  struct sockaddr_in addr = {};

  // IPv4
  addr.sin_family = AF_INET;
  // Network TO Host Short, usually for set port, need a 16-bit-value
  addr.sin_port = ntohs(1234);
	// Network TO Host Long, usually for set address, need a 32-bit-value
  addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);  

  int rv = connect(fd, (const struct sockaddr*)&addr, sizeof(addr));
  if (rv) {
    die("connect");
  }

  char msg[] = "hello";
  write(fd, msg, strlen(msg));

  char rbuf[64] = {};
  ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
  if (n < 0) {
    die("read");
  }
  printf("server says: %s\n", rbuf);
  close(fd);
}

int main(int argc, char** argv) {
  start_client();
  return 0;
}
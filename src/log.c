#include "log.h"

#include <stdio.h>  // puts, fputs
#include <stdlib.h> // exit(STATUS)

void msg(const char *msg) { puts(msg); }
void die(const char *msg) {
  fputs(msg, stderr);
  exit(1);
}
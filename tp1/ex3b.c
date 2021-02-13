#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bye() { printf("That was all, folks\n"); }

int main() {
  int i = atexit(bye); // register bye as exit handler
  if (i != 0) {
    fprintf(stderr, "cannot set exit function\n");
    exit(EXIT_FAILURE);
  }
  
  printf("In main function for 3 seconds ...\n");
  sleep(3);
  printf("Time is up. Calling exit handlers...\n");
}

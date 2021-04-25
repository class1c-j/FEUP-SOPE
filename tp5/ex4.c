#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <time.h>

int main() {
  printf("ticks per second: %d\n", CLOCKS_PER_SEC);
}

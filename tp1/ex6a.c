#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int f = open(argv[1], O_RDONLY);
  if (f == -1) {
    printf("error opening the file\n");
  } else {
    close(f);
  }
}

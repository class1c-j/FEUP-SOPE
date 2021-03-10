#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  int p1[2]; // C -> P
  int p2[2]; // P -> C

  if (pipe(p1) < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  if (pipe(p2) < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  int pid;
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) { // child
    close(p2[1]);
    close(p1[0]);

    char operating[20];
    char systems[8] = "Systems";
    if (read(p2[0], operating, 11) < 0) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    strcat(operating, systems);
    printf("Child says : %s\n", operating);

    if (write(p1[1], systems, 8) < 0) {
      perror("write");
      exit(EXIT_FAILURE);
    }

    close(p2[0]);
    close(p1[1]);
  } else { // parent
    close(p2[0]);
    close(p1[1]);

    char operating[20] = "Operating ";
    char systems[8];
    if (write(p2[1], operating, 11) < 0) {
      perror("write");
      exit(EXIT_FAILURE);
    }

    if (read(p1[0], systems, 8) < 0) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    strcat(operating, systems);
    printf("Parent says : %s\n", operating);

    close(p2[1]);
    close(p1[0]);
  }
}
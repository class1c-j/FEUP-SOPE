#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  int fd[2];
  if (pipe(fd) < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  int pid;
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) { // child
    close(fd[1]);

    char operating[20];
    char systems[8] = "Systems";
    if (read(fd[0], operating, 11) < 0) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    strcat(operating, systems);
    printf("Child says : %s\n", operating);

    close(fd[0]);
  } else { // parent
    close(fd[0]);
    char operating[20] = "Operating ";
    if (write(fd[1], operating, 11) < 0) {
      perror("write");
      exit(EXIT_FAILURE);
    }
    close(fd[1]);
  }
}
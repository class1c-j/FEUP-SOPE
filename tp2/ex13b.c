#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  if (mkfifo("/tmp/np13b", 0666) < 0) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }

  int pid;
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) { // child
    int np;
    while ((np = open("/tmp/np13b", O_RDONLY)) < 0)
      ; // synchronization

    char operating[20];
    char systems[8] = "Systems";
    if (read(np, operating, 11) < 0) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    strcat(operating, systems);
    printf("Child says : %s\n", operating);

    close(np);
  } else { // parent
    int np;
    while ((np = open("/tmp/np13b", O_WRONLY)) < 0)
      ;
    char operating[20] = "Operating ";
    if (write(np, operating, 11) < 0) {
      perror("write");
      exit(EXIT_FAILURE);
    }
    close(np);
  }
}
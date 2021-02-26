#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  pid_t pid = fork();
  pid_t child_pid;
  int status;
  switch (pid) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    printf("Hello, ");
    break;
  default:
    child_pid = wait(&status); // waits for child's return
    if (child_pid < 0) {
      perror("child terminated");
      exit(EXIT_FAILURE);
    }
    printf("World\n");
    break;
  }
}

// no, the child does not have info on the parent's status;
// we could make the parent send a signal atexit and make the
// child catch that signal

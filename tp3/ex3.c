#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sig_handler(int sig_no) {
  printf("Process %d recieved signal %d\n", getpid(), sig_no);
}

int main() {
  struct sigaction sig_action;
  memset(&sig_action, 0, sizeof(struct sigaction));
  sig_action.sa_handler = sig_handler;
  if (sigaction(SIGINT, &sig_action, NULL) < 0) {
    perror("sigaction: SIGINT");
    exit(EXIT_FAILURE);
  }
  sig_action.sa_handler = sig_handler;
  if (sigaction(SIGUSR1, &sig_action, NULL) < 0) {
    perror("sigaction: SIGUSR1");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    int cpid = fork();
    if (cpid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (cpid == 0) {  // child
      printf("Child; PID: %d; Session: %d ; Group: %d;\n", getpid(),
             getsid(cpid), getpgrp());
    } else {  // parent
      printf("Parent; PID: %d; Session: %d ; Group: %d;\n", getpid(),
             getsid(cpid), getpgrp());
    }
  } else {  // grandparent
    printf("Grandparent; PID: %d ; Session: %d ; Group: %d;\n", getpid(),
           getsid(pid), getpgrp());
  }
  sleep(20);
}

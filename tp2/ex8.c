#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signo) { fprintf(stderr, "Hello!\n"); }

int main() {
  struct sigaction new, old;
  sigset_t smask; // defines signals to block while func() is running

  // prepare struct sigaction
  if (sigemptyset(&smask) == -1) // block no signal
    perror("sigsetfunctions");
  new.sa_handler = signal_handler;
  new.sa_mask = smask;
  new.sa_flags = 0; // usually works

  if (sigaction(SIGUSR1, &new, &old) == -1)
    perror("sigaction");

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    _exit(EXIT_FAILURE);
  }

  if (pid == 0) { // child
    pause();
  }

  else { // parent
    printf("World: ");
    kill(pid, SIGUSR1);
  }
}
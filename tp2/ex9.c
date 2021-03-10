#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 3

void *rot(void *i) {
  *(int *)i *= *((int *)i);
  printf("\n\t In thread PID: %d ; TID: %lu.", getpid(),
         (unsigned long)pthread_self());
  sleep(2);
  pthread_exit(i);
}

int main() {
  int i;                   // thread counter
  pthread_t ids[NTHREADS]; // storage of (system) Thread Identifiers

  setbuf(stdout, NULL); // only for debugging
  printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(),
         (unsigned long)pthread_self());

  // new threads creation
  for (i = 0; i < NTHREADS; i++) {
    int *arg = (int *)malloc(sizeof(*arg));
    if (arg == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    *arg = i;
    if (pthread_create(&ids[i], NULL, rot, (void *)arg) != 0)
      exit(-1); // here, we decided to end process
    else
      printf("\nNew thread %d ; TID: %lu.", i, (unsigned long)ids[i]);
  }
  // wait for finishing of created threads
  for (i = 0; i < NTHREADS; i++) {
    void *status = 0;
    pthread_join(ids[i], &status); // Note: threads give no termination code
    printf("\nTermination of thread %d: %lu.\n", i, (unsigned long)ids[i]);
    printf("returned with %d\n", *((int *)status));
  }

  printf("\n");
  pthread_exit(NULL); // here, not really necessary...
  return 0;           // will not run this!
}

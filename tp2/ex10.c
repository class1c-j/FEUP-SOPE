#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct arg_t {
  char *message;
  int order;
} arg_t;

#define N_THREADS 2
static int done = 0;  // ew

void *thr_func(void *a) {
  arg_t *args = (arg_t *)a;
  if (args->order == 0) {
    printf("%s", args->message);
    done = 1;
  }
  else if (args->order == 1) {
    while (!done) {
      sleep(1);
    }
    printf("%s", args->message);
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t ids[N_THREADS];
  arg_t args[N_THREADS];

  args[0].order = 0;
  args[0].message = "Operating ";
  args[1].order = 1;
  args[1].message = "Systems\n";

  for (int i = 0; i < N_THREADS; ++i) {
    if (pthread_create(&ids[i], NULL, thr_func, &args[i]) != 0) {
      exit(-1);
    }
  }
  for (int i = 0; i < N_THREADS; ++i) {
    void *status;
    pthread_join(ids[i], &status);
  }
  pthread_exit(NULL);
}
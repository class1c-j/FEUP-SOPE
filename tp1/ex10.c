#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>

#define LOOPS 100000

int main() {
  clock_t start, end;
  struct tms t;
  long ticks;

  /* start measuring time */
  start = times(&t);
  ticks = sysconf(_SC_CLK_TCK);

  for (int i = 0; i < LOOPS; ++i) {
    printf("Hello, World!\n");
  }

  printf("\nClock ticks per second: %ld\n", ticks);

  /* finish measuring time */
  end = times(&t);

  printf("Clock:                %4.3f s\n", (double)(end - start) / ticks);
  printf("User time:            %4.3f s\n", (double)t.tms_utime / ticks);
  printf("System time:          %4.3f s\n", (double)t.tms_stime / ticks);
  printf("Children user time:   %4.3f s\n", (double)t.tms_cutime / ticks);
  printf("Children system time: %4.3f s\n", (double)t.tms_cstime/ticks);

}
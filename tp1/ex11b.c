#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Wrong command. Try '%s [file1] [file2]'\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *f1 = fopen(argv[1], "r");
  if (f1 == NULL) {
    perror("Error opening file1");
    exit(EXIT_FAILURE);
  }

  FILE *f2 = fopen(argv[2], "w");

  char buf[BUFFER_SIZE];
  ssize_t bytes_read = 0, bytes_written = 0;

  while ((bytes_read = fread(buf, sizeof(char), sizeof(buf), f1)) != 0) {
    if (bytes_read < 0) {
      fprintf(stderr, "Error reading from %s", argv[1]);
    }
    bytes_written = fwrite(buf, sizeof(char), bytes_read, f2);
    if (bytes_written < 0) {
      fprintf(stderr, "Error writing to %s", argv[2]);
    }
  }

  fclose(f1);
  fclose(f2);
}
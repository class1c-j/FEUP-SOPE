#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Wrong command. Try '%s [file1] [file2]'\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int f1 = open(argv[1], O_RDONLY);
  if (f1 == -1) {
    perror("Error opening file1");
    exit(EXIT_FAILURE);
  }

  int f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);

  char buf[BUFFER_SIZE];
  ssize_t bytes_read = 0, bytes_written = 0;

  while ((bytes_read = read(f1, buf, BUFFER_SIZE)) != 0) {
    if (bytes_read < 0) {
      fprintf(stderr, "Error reading from %s", argv[1]);
    }
    bytes_written = write(f2, buf, bytes_read);
    if (bytes_written < 0) {
      fprintf(stderr, "Error writing to %s", argv[2]);
    }
  }

  close(f1);
  close(f2);
}
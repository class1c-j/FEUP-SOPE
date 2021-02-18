#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#define MAX_PATH_SIZE 256

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Wrong command. Try '%s [path]'", argv[0]);
  }

  DIR *dir = opendir(argv[1]);
  struct dirent *dirent;

  if (dir == NULL) {
    fprintf(stderr, "Error opening directory %s\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  while ((dirent = readdir(dir)) != NULL) {
    if (dirent->d_type == DT_REG) {
      char file_path[MAX_PATH_SIZE + sizeof('/')];
      sprintf(file_path, "%s/%s", argv[1], dirent->d_name);
      struct stat st;
      size_t size = 0;
      if (stat(file_path, &st) == 0) {
        size = st.st_size;
      } else {
        perror("Error calling stat\n");
        exit(EXIT_FAILURE);
      }
      printf("%s: %ld bytes\n", dirent->d_name, size);
    }
  }
  closedir(dir);
}
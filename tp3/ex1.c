#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void traverse_dir(char *path) {
  DIR *dp;
  if ((dp = opendir(path)) == NULL) {
    perror("opendir");
    exit(EXIT_FAILURE);
  }
  struct dirent *dirent;
  while ((dirent = readdir(dp)) != NULL) {
    if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
      char file_path[PATH_MAX];
      snprintf(file_path, PATH_MAX, "%s/%s", path, dirent->d_name);
      struct stat st;
      if (stat(file_path, &st) < 0) {
        perror("stat");
        exit(EXIT_FAILURE);
      }
      printf("%s : %ld\n", file_path, st.st_size);
      if (dirent->d_type == DT_DIR) {
        int pid;
        if ((pid = fork()) < 0) {
          perror("fork");
          exit(EXIT_FAILURE);
        }
        if (pid == 0) {  // child
          traverse_dir(file_path);
        } else {  // parent
          wait(NULL);
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  char current_dir[PATH_MAX];
  if (getcwd(current_dir, PATH_MAX) == NULL) {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }
  traverse_dir(current_dir);
}

#include <stdio.h>
#include <string.h>

int find(char *string, char *array[], int array_size) {
  for (int i = 0; i < array_size; ++i) {
    if (strcmp(string, array[i]) == 0) {
      return 0;
    }
  }
  return -1;
}

int main(int argc, char *argv[], char *envp[]) {
  for (int i = 0; envp[i] != NULL; ++i) {
    char *envar_name = strtok(envp[i], "=");
    if (find(envar_name, argv, argc) == 0) {
      printf("Environment variable %s set as %s\n", envar_name,
             strtok(NULL, "="));
    }
  }
}
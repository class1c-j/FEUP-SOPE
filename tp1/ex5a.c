#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {

  printf("Name of the program: %s\n", argv[0]);

  printf("Command line arguments: ");
  for (int i = 1; i < argc; ++i) {
    printf("%s ", argv[i]);
  }
  printf("\n");

  printf("Environment variables: ");
  for (int i = 0; envp[i] != NULL; ++i) {
    printf("%s\n", envp[i]);
  }
  printf("\n");
}
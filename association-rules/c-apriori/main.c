#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parseTransaction(char*);

int main(int argc, char *argv[]) {

  float sup;
  float conf;

  FILE* inputFile;
  char* line;
  size_t len = 0;
  ssize_t read;

  char** transaction;

  int i;
  for (i = 0; i < argc; i++) {
    if (strcmp("-s", argv[i]) == 0 && i + 1 < argc) {
      printf("%s\n", argv[i + 1]);
      sup = atof(argv[i + 1]);
    }
    if (strcmp("-c", argv[i]) == 0 && i + 1 < argc) {
      printf("%s\n", argv[i + 1]);
      conf = atof(argv[i + 1]);
    }
  }

  inputFile = fopen("input.txt", "r");
  if (inputFile == NULL) {
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, inputFile)) != 1) {
    transaction = parseTransaction(line);
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parse_transaction(char*);

int main(int argc, char *argv[]) {

  float sup;
  float conf;

  FILE* input_file;
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

  input_file = fopen("input.txt", "r");
  if (input_file == NULL) {
    exit(EXIT_FAILURE);
  }

  i = 0;
  while ((read = getline(&line, &len, input_file)) != -1) {
    line[strlen(line) - 1] = '\0';
    transaction = parse_transaction(line);
    i++;
  }

  sup *= i;

  fclose(input_file);

  return 0;
}

char** parse_transaction(char* line) {
  char** tran;
  char* line_cp = (char*)malloc(strlen(line) + 1);
  char* item;
  int i = 0;
  strcpy(line_cp, line);

  item = strtok(line_cp, " ");
  while (item != NULL) {
    i++;
    item = strtok(NULL, " ");
  }
  tran = (char**)malloc(i * sizeof(char*));

  return tran;
}

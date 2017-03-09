#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parse_transaction(char*, int*);

int main(int argc, char *argv[]) {

  float sup;
  float conf;

  FILE* input_file;
  char* line;
  size_t len = 0;
  ssize_t read;

  int i;
  for (i = 0; i < argc; i++) {
    if (strcmp("-s", argv[i]) == 0 && i + 1 < argc) {
      sup = atof(argv[i + 1]);
    }
    if (strcmp("-c", argv[i]) == 0 && i + 1 < argc) {
      conf = atof(argv[i + 1]);
    }
  }

  input_file = fopen("input.txt", "r");
  if (input_file == NULL) {
    exit(EXIT_FAILURE);
  }

  i = 0;
  while ((read = getline(&line, &len, input_file)) != -1) {
    char** transaction;
    int data_length;
    line[strlen(line) - 1] = '\0';
    transaction = parse_transaction(line, &data_length);
    i++;
    free(transaction);
  }

  sup *= i;

  fclose(input_file);

  return 0;
}

char** parse_transaction(char* line, int* length) {
  char** tran;
  char* line_cp1 = (char*)malloc(strlen(line) + 1);
  char* line_cp2 = (char*)malloc(strlen(line) + 1);
  char* item;
  int i = 0;

  strcpy(line_cp1, line);
  strcpy(line_cp2, line);

  item = strtok(line_cp1, " ");
  while (item != NULL) {
    i++;
    item = strtok(NULL, " ");
  }

  tran = (char**)malloc(i * sizeof(char*));

  item = strtok(line_cp2, " ");
  i = 0;
  while (item != NULL) {
    tran[i++] = item;
    item = strtok(NULL, " ");
  }

  *length = i;

  free(line_cp1);
  free(line_cp2);
  free(item);

  return tran;
}

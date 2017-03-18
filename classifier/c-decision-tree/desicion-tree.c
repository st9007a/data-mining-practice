#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

  char* training_file_name = NULL;
  char* test_file_name = NULL;

  FILE* training_file;
  FILE* test_file;
  char* line;
  size_t len = 0;
  ssize_t read;

  int i;

  for (i = 0; argv[i]; i++) {
    if (strcmp(argv[i], "--train") == 0 && argv[i + 1]) {
      training_file_name = argv[i + 1];
    }
    if (strcmp(argv[i], "--test") == 0 && argv[i + 1]) {
      test_file_name = argv[i + 1];
    }
  }

  if (training_file_name == NULL || test_file_name == NULL) {
    printf("Error: Loss training data or test data.\n");
    exit(EXIT_FAILURE);
  }

  training_file = fopen(training_file_name, "r");
  if (training_file == NULL) {
    printf("Error: Training data is not found.\n");
    exit(EXIT_FAILURE);
  }

  while((read = getline(&line, &len, training_file)) != -1) {
    line[strlen(line) - 1] = 0;
    printf("%s", line);
  }

  return 0;
}

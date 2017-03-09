#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  float sup;
  float conf;

  FILE* inputFile;

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

  printf("s: %f, c: %f\n", sup, conf);

  return 0;
}

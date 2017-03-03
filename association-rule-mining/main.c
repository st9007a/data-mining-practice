#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fpTree.c"

int main(int argc, char** argv) {

  float minSup;
  float minConf;
  int countOfMinSup;

  FILE* record;
  char* line;
  size_t len = 0;
  ssize_t read;

  struct array headerTable;

  printf("Input your minimum support(0 ~ 1) : ");
  scanf("%f", &minSup);

  printf("Input your minimum confidence(0 ~ 1) : ");
  scanf("%f", &minConf);

  record = fopen("input.txt", "r");
  newArray(&headerTable, 1);

  if (record == NULL) {
    printf("Read File Error : Can't find a file named input.txt\n");
    exit(1);
  }

  printf("scanf input.txt\n");
  while ((read = getline(&line, &len, record)) != -1) {
    line[strlen(line) - 1] = '\0';
    addToHeaderTable(&headerTable, line);
  }
  countOfMinSup = ceil(minSup * headerTable.used);

  printf("sort header table\n");
  headerTable = quickSort(headerTable);

  printf("remove item less than minimum support\n");

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "fpTree.c"

int main(int argc, char** argv) {

  float minSup;
  float minConf;

  FILE* record;
  char* line;
  size_t len = 0;
  ssize_t read;

  struct array* headerTable;

  printf("Input your minimum support : ");
  scanf("%f", &minSup);

  printf("\nInput your minimum confidence : ");
  scanf("%f", &minConf);

  record = fopen("input.txt", "r");

  if (record == NULL) {
    printf("Read File Error : Can't find a file named input.txt\n");
    exit(1);
  }

  while ((read = getline(&line, &len, record)) != -1) {
    addToHeaderTable(headerTable, line);
  }

  int i;
  for (i = 0; i < headerTable->used; i++) {
    printf("%s : %lu", headerTable->items[i].item, headerTable->items[i].frequency);
  }

  return 0;
}

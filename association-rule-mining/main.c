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

  struct array headerTable;

  printf("Input your minimum support : ");
  scanf("%f", &minSup);

  printf("Input your minimum confidence : ");
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

  printf("sort header table\n");
  headerTable = quickSort(headerTable);

  printf("print result\n");
  int i;
  for (i = 0; i < headerTable.used; i++) {
    printf("item: %s, count: %lu\n", headerTable.items[i].item, headerTable.items[i].frequency);
  }

  return 0;
}

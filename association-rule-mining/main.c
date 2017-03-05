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

  int i;
  struct array headerTable;
  struct fpTree rootNode = fpTreeDefault;

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
    int listLen;
    char** list;
    line[strlen(line) - 1] = '\0';
    list = parseLine(line, &listLen);
    addToHeaderTable(&headerTable, list, listLen);
  }
  countOfMinSup = ceil(minSup * headerTable.used);

  printf("sort header table\n");
  headerTable = quickSort(headerTable);


  printf("remove item less than minimum support\n");
  for (i = 0; i < headerTable.used; i++) {
    if (headerTable.items[i].frequency >= countOfMinSup) {
      removeMultiItems(&headerTable, 0, i - 1);
      break;
    }
  }

  for (i = 0; i < headerTable.used; i++) {
    printf("items item: %s, count: %lu\n", headerTable.items[i].item, headerTable.items[i].frequency);
  }

  printf("Rescanf input.txt to build fp tree\n");

  fseek(record, 0, SEEK_SET);
  while ((read = getline(&line, &len, record)) != -1) {
    char** list;
    int listLen;
    line[strlen(line) - 1] = '\0';
    list = parseLine(line, &listLen);
    list = removeNotSupportItems(&headerTable, list, &listLen);
    sortList(&headerTable, list, listLen);
    insertToFPTree(&headerTable, &rootNode, list, listLen, 1);
  }

  return 0;
}

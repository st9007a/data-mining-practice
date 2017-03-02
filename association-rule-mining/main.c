#include <stdio.h>
#include <stdlib.h>
#include "fpTree.c"

int main(int argc, char** argv) {

  struct array arr;
  struct frequencyItem f1;
  struct frequencyItem f2;
  struct frequencyItem f3;
  newArray(&arr, 3);
  f1.item = "123";
  f2.item = "456";
  f3.item = "789";
  push(&arr, f1);
  push(&arr, f2);
  push(&arr, f3);

  int i;
  for(i=0;i<arr.used;i++) {
    printf("%s\n", arr.items[i].item);
  }

  return 0;

  float minSup;
  float minConf;

  FILE* record;
  char* line;
  size_t len = 0;
  ssize_t read;

  struct frequencyItem* headerTable;

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

  }

  return 0;
}

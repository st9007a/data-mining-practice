#include <stdio.h>
#include <stdlib.h>
#include "fpTree.c"

int main(int argc, char** argv) {

  struct array arr;
  struct frequencyItem f1;
  struct frequencyItem f2;
  struct frequencyItem f3;
  struct frequencyItem f4;
  struct frequencyItem f5;
  struct frequencyItem f6;
  struct frequencyItem f7;
  newArray(&arr, 3);
  f1.frequency = 10;
  f2.frequency = 2;
  f3.frequency = 20;
  f4.frequency = 5;
  f5.frequency = 12;
  f6.frequency = 1;
  f7.frequency = 1;
  push(&arr, f1);
  push(&arr, f2);
  push(&arr, f3);
  push(&arr, f4);
  push(&arr, f5);
  push(&arr, f6);
  push(&arr, f7);

  arr = quickSort(arr);

  printf("for each\n");

  int i;
  for (i = 0; i < arr.used; i++) {
    printf("arr %lu\n", arr.items[i].frequency);
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

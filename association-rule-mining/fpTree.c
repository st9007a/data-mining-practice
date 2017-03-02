#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fpTree.h"

void addToHeaderTable(struct frequencyItem* headerTable, char* line) {
  char* token = " ";
  char* item;

  for(item = strtok(line, token); item != NULL; item = strtok(NULL, token)) {
    int i;
    int flag = 0;
    for(i=0; (headerTable + i) != NULL; i++) {
      if(strcmp((headerTable + i)->item, item) == 0) {
        (headerTable + i)->frequency++;
        flag++;
        break;
      }
    }
    if(flag == 0) {
      struct frequencyItem f;
      f.frequency = 1;
      f.item = item;
      *(headerTable + i) = f;
    }
  }
}

struct frequencyItem* concatStruct(struct frequencyItem* arr1, struct frequencyItem* arr2) {
  struct frequencyItem* arr;
  int i, j;
  for(i = 0; (arr1 + i) != NULL; i++) {
    *(arr + i) = *(arr1 + i);
  }
  for(j = 0; (arr2 + j) != NULL; j++) {
    *(arr + j + i) = *(arr2 + j);
  }
  return arr;
}

struct frequencyItem* sortHeaderTable(struct frequencyItem* headerTable, int len) {
  struct frequencyItem* less;
  struct frequencyItem* greater;
  if(len == 0) {
    return headerTable;
  }
  else {
    struct frequencyItem* pivot = headerTable + len - 1;
    int i;
    for(i = 0; i < len; i++) {
      if((headerTable + i)->frequency < pivot->frequency) {
        *(less + 1) = *(headerTable + i);
      }
      else {
        *(greater + 1) = *(headerTable + i);
      }
    }
    return concatStruct(concatStruct(less, pivot), greater);
  }
}

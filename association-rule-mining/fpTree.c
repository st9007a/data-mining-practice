#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fpTree.h"
#include "array.c"

void addToHeaderTable(struct array* headerTable, char* line) {
  char* token = " ";
  char* item;

  for(item = strtok(line, token); item != NULL; item = strtok(NULL, token)) {
    int i;
    int flag = 0;
    for(i=0; i<headerTable->size; i++) {
      if(strcmp(headerTable->array[i]->item, item) == 0) {
        headerTable->array[i]->frequency++;
        flag++;
        break;
      }
    }
    if(flag == 0) {
      struct frequencyItem f;
      f.frequency = 1;
      f.item = item;
      push(headerTable, f);
    }
  }
}

struct array* concatStruct(struct array* arr1, struct array* arr2) {
  struct array* arr;
  int i, j;

  newArray(arr, arr1->used + arr2->used);

  for(i = 0; i < arr1->used; i++) {
    push(arr, *(arr1->array[i]));
  }
  for(j = 0; j < arr2->used; j++) {
    push(arr, *(arr2->array[j]));
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

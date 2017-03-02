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
    for(i=0; i<headerTable->used; i++) {
      if(strcmp(headerTable->items[i].item, item) == 0) {
        headerTable->items[i].frequency++;
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

struct array concatStruct(struct array arr1, struct array arr2) {
  struct array arr;
  int i, j;

  newArray(&arr, arr1.used + arr2.used);

  for(i = 0; i < arr1.used; i++) {
    push(&arr, arr1.items[i]);
  }
  for(j = 0; j < arr2.used; j++) {
    push(&arr, arr2.items[j]);
  }
  return arr;
}

struct array sortHeaderTable(struct array headerTable) {
  struct array less;
  struct array greater;
  if(headerTable.used == 0) {
    return headerTable;
  }
  else {
    struct frequencyItem pivot = headerTable.items[headerTable.used - 1];
    int i;
    for(i = 0; i < headerTable.used; i++) {
      if(headerTable.items[i].frequency < pivot.frequency) {
        push(&less, headerTable.items[i]);
      }
      else {
        push(&greater, headerTable.items[i]);
      }
    }
    push(&less, pivot);
    return concatStruct(less, greater);
  }
}

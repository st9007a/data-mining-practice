#include "array.h"

void newArray(struct array* arr, size_t size) {
  arr->items = malloc(sizeof(struct frequencyItem) * size);
  arr->size = size;
  arr->used = 0;
}

void push(struct array* arr, struct frequencyItem element) {
  if(arr->used == arr->size) {
    arr->size *= 2;
    arr->items = (struct frequencyItem*)realloc(arr->items, arr->size * sizeof(struct frequencyItem));
  }
  arr->items[arr->used++] = element;
}

struct array concat(struct array arr1, struct array arr2) {
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

struct array quickSort(struct array headerTable) {
  struct array less;
  struct array greater;
  newArray(&less, 1);
  newArray(&greater, 1);
  if(headerTable.used == 0) {
    return headerTable;
  }
  else {
    struct frequencyItem pivot = headerTable.items[headerTable.used - 1];
    int i;
    for(i = 0; i < headerTable.used - 1; i++) {
      if(headerTable.items[i].frequency < pivot.frequency) {
        push(&less, headerTable.items[i]);
      }
      else {
        push(&greater, headerTable.items[i]);
      }
    }
    less = quickSort(less);
    push(&less, pivot);
    return concat(less, quickSort(greater));
  }
}

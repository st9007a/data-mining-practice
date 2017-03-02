#include "array.h"

void newArray(array* arr, size_t size) {
  arr->items = malloc(sizeof(struct frequencyItem) * size);
  arr->size = size;
  arr->used = 0;
}

void push(array* arr, struct frequencyItem element) {
  if(arr->used == arr->size) {
    arr->size *= 2;
    arr->array = (struct frequencyItem*)realloc(arr->array, arr->size * sizeof(struct frequencyItem));
  }
  arr->array[arr->used++] = element;
}

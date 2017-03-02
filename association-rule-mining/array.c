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

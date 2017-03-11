#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charArrLib.h"

void init_string_array(struct string_array* s_arr, size_t size) {
  s_arr->size = size;
  s_arr->length = 0;
  s_arr->array = (char**)malloc(sizeof(char*) * size);
}

void push(struct string_array* s_arr, char* item) {
  if (s_arr->size == s_arr->length) {
    s_arr->size *= 2;
    s_arr->array = (char**)realloc(s_arr->array, s_arr->size * sizeof(char*));
  }
  s_arr->array[s_arr->length++] = item;

}
void filter_item(struct string_array* s_arr, char* target, int (*checkFunction)(char*, char*)) {
  int i, j;
  int len = 0;
  for (i = 0; s_arr->array[i]; i++) {
    if (checkFunction(s_arr->array[i], target) == 1) {
      for (j = i; s_arr->array[j]; j++) {
        s_arr->array[j] = s_arr->array[j + 1];
        len++;
      }
    }
  }
  s_arr->array = (char**)realloc(s_arr->array, len * sizeof(char*));
}

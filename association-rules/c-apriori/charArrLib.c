#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charArrLib.h"


void push(struct stringArray* sArr, char* item) {
  if (sArr->size == sArr->length) {
    sArr->size *= 2;
    sArr->array = (char**)realloc(sArr->array, sArr->size * sizeof(char*));
  }
  sArr->array[sArr->length++] = item;

}
void filter_item(struct stringArray* sArr, char* target, int (*checkFunction)(char*, char*)) {
  int i, j;
  int len = 0;
  for (i = 0; sArr->array[i]; i++) {
    if (checkFunction(sArr->array[i], target) == 1) {
      for (j = i; sArr->array[j]; j++) {
        sArr->array[j] = sArr->array[j + 1];
        len++;
      }
    }
  }
  sArr->array = (char**)realloc(sArr->array, len * sizeof(char*));
}

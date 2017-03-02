#ifndef ARRAY
#define ARRAY

#include "fpTree.h"

struct array {
  size_t size;
  size_t used;
  struct frequencyItem* items;
}

void newArray(array*, size_t);
void push(array*, struct frequencyItem);

#endif

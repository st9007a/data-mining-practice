#ifndef FPTREE
#define FPTREE

#include "array.h"

struct fpTree {
  char* item;
  size_t count;
  struct fpTree* parent;
  struct fpTree* children;
  struct fpTree* link;
};

struct frequencyItem {
  char* item;
  size_t frequency;
  struct fpTree* link;
};

void addToHeaderTable(struct array*, char*);
struct array sortHeaderTable(struct array);
struct array concatStruct(struct array, struct array);

#endif

#ifndef FPTREE
#define FPTREE

#include "array.h"

struct fpTree {
  char* item;
  size_t count;
  size_t childrenLen;
  size_t childrenSize;
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
void removeNotSupportItems(struct array*, char*, char**, int*);
void sortList(struct array*, char**, int);
void buildLink(struct array*, struct fpTree*);
void insertToFPTree(struct array*, struct fpTree*, char**, int);

#endif

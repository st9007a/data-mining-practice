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
  size_t condCount;
} fpTreeDefault = { "", 1, 0, 0, NULL, NULL, NULL, 0 };

struct frequencyItem {
  char* item;
  size_t frequency;
  struct fpTree* link;
};

char** parseLine(char*, int*);
void addToHeaderTable(struct array*, char**, int, int);
void removeNotSupportItems(struct array*, char**, int*);
void sortList(struct array*, char**, int);
void buildLink(struct array*, struct fpTree*);
void insertToFPTree(struct array*, struct fpTree*, char**, int, int);

char** getPrefixPath(struct fpTree*, int*, int*);
void miningTree(struct array*, struct fpTree*, int ,float, char**);

#endif
